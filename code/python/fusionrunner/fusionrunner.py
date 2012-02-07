#!/usr/bin/python
""" FusionRunner

Queries Google Fusion Tables for MyTracks data.
"""
__author__ = 'hardware.hank@gmail.com (Erik Gregg)'
### IMPORTS ###
import sys 
sys.path.append("./fusion-tables-client-python-read-only/src/")
sys.path.append("./httplib2/python2")
import getpass, httplib2, urllib, re, string
from datetime import datetime, timedelta
from authorization.oauth import OAuth
from sql.sqlbuilder import SQL
import ftclient
import pprint
pp = pprint.PrettyPrinter(indent=4)
from BeautifulSoup import BeautifulSoup

### Fusion Tables Authentication ###
print "Authenticating with Google...",
consumer_key = "207320244638.apps.googleusercontent.com"
try:
  with open('secret', 'r') as f:
    consumer_secret = f.readline().rstrip()
except IOError:
  print "No consumer secret."
  sys.exit(-1)

try:
  with open('oauth_cached_data', 'r') as f:
    token, secret = [x.rstrip() for x in f.readlines()]
except IOError:
  print "No cached OAuth data.  Initiating new request..."
  url, token, secret = OAuth().generateAuthorizationURL(consumer_key, consumer_secret, consumer_key)
  print "Visit this URL in a browser: "
  print url
  raw_input("Hit enter after authorization")
  token, secret = OAuth().authorize(consumer_key, consumer_secret, token, secret)
  with open('oauth_cached_data', 'w') as f:
    f.write(token + "\n" + secret)

oauth_client = ftclient.OAuthFTClient(consumer_key, consumer_secret, token, secret)
print "Success"

### Smashrun Authentication ### 
# Using some awesome login action and this handy JSON endpoint:
# http://smashrun.com/services/running-jsonservice.asmx
try:
  with open('smashrun_secret', 'r') as f:
      smashrun_secret = f.readline().rstrip()
except IOError:
  print "No Smashrun secret - can't authenticate.  Make a smashrun_secret file with your password."
  sys.exit(-1)

print "Authenticating with Smashrun...",
smashrun_url = "http://smashrun.com/services/user-jsonservice.asmx/LoginUser"
smashrun_body = '{"loginEmail":"smashrun.hardwarehank@ralree.com","loginPassword":"%s"}' % (smashrun_secret)
smashrun_headers = {
            'Content-Type': 'application/json; charset=UTF-8',
            'Referer': 'http://smashrun.com/login',
          }
smashrun_http = httplib2.Http()
smashrun_response, smashrun_content = smashrun_http.request(smashrun_url, 'POST', 
                                                   headers=smashrun_headers, body=smashrun_body)
smashrun_headers['Cookie'] = smashrun_response['set-cookie']
del smashrun_headers['Referer']
print "Success"

### List smashrun runs ###

smashrun_url = "http://smashrun.com/hank/list"
smashrun_response, smashrun_content = smashrun_http.request(smashrun_url, 'GET')
soup = BeautifulSoup(smashrun_content)
ids = [int(x['id']) for x in soup.findAll('tr', id=re.compile('\d+'))]

smashrun_url = "http://smashrun.com/services/running-jsonservice.asmx/GetRunListItem"
dates = []
for i in ids:
  smashrun_body = '{"runId":"%d","unit":"m"}' % (i)
  smashrun_response, smashrun_content = smashrun_http.request(smashrun_url, 'POST', 
                                      headers=smashrun_headers, body=smashrun_body)
  date = re.search(r'startDateTime":new Date\((.*?)\),', smashrun_content).group(1)
  # The extracted start date
  date = datetime.fromtimestamp(float(date)/1000)
  dates.append(date)

### Fusion Tables queries ###
fusion_results = [ x.split(",") for x in oauth_client.query(SQL().showTables()).split("\n")[1:-1] ]

for table in fusion_results:
  rows = oauth_client.query(SQL().select(int(table[0]), ['description'], "name LIKE '%(End)'"))
  desc = rows.split("\n")[1]
  # Grab fusion table fields with regex.
  strdate = re.search(r'Recorded: (.*?)<br>', desc).group(1)
  start_date_time = datetime.strptime(strdate, "%m/%d/%y %I:%M %p")
  # Check if we already recorded it using the data we collected from SmashRun
  date_diffs = [x - start_date_time for x in dates]
  date_diffs = [x for x in date_diffs if x.total_seconds() == 0]
  if len(date_diffs) > 0:
    # We already imported this.  Alert the user and move on.
    print "Already imported run from", start_date_time, ".  Skipping..."
    continue
  start_date_time = start_date_time.isoformat()

  distance_km = re.search(r'Total distance: (.*?) km', desc).group(1)

  total_time = re.search(r'Moving time: (.*?)<br>', desc).group(1)
  m = re.match(r'(\d+):(\d+):(\d+)|(\d+):(\d+)', total_time) 
  groups = [x for x in m.groups() if x != None]
  if len(groups) == 2:
    total_time = timedelta(minutes=int(groups[0]), seconds=int(groups[1]))
  else:
    total_time = timedelta(hours=int(groups[0]), minutes=int(groups[1]), seconds=int(groups[2]))
  total_time = int(total_time.total_seconds() * 1000)

  activity = re.search(r'Activity type: (\w+)', desc).group(1)
  tagid = None
  if activity == 'walking':
    activity = 'Walk'
    tagid = 2
  if activity == 'race':
    activity = 'Race'
    tagid = 2

  # Save the run
  print "Adding Run from %s..." % (start_date_time),
  smashrun_url = "http://smashrun.com/services/running-jsonservice.asmx/SaveRunListItem"
  smashrun_body = '{"runListItem": { "distance":"%s", "bookedUnitCode":"k", "viewunitcode":"m", "startDateTime":"%s", "duration":%d, "runId":null }}' % (distance_km, start_date_time, total_time)
  smashrun_response, smashrun_content = smashrun_http.request(smashrun_url, 'POST', 
                                                              headers=smashrun_headers, body=smashrun_body)
  if smashrun_response['status'] == "200":
    print "Success"

  if tagid != None:
    print "Tagging Run from %s..." % (start_date_time),
    match = re.search(r'"runId":(\d+)', smashrun_content)
    runid = int(match.group(1))
    smashrun_url = "http://smashrun.com/services/running-jsonservice.asmx/SaveRunTag"
    smashrun_body = '{"runId":%d,"tagId":%d,"text":"%s",untag:false}' % (runid, tagid, activity)
    smashrun_response, smashrun_content = smashrun_http.request(smashrun_url, 'POST', 
                                                                headers=smashrun_headers, body=smashrun_body)
    if smashrun_response['status'] == "200":
      print "Success"
