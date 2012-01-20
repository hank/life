#!/usr/bin/python
""" FusionRunner

Queries Google Fusion Tables for MyTracks data.
"""
__author__ = 'hardware.hank@gmail.com (Erik Gregg)'
import sys, getpass
sys.path.append("./fusion-tables-client-python-read-only/src/")
sys.path.append("./httplib2/python2")
from authorization.oauth import OAuth
from sql.sqlbuilder import SQL
import ftclient
import pprint
pp = pprint.PrettyPrinter(indent=4)

import httplib2, urllib

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

# show tables
results = [ x.split(",") for x in oauth_client.query(SQL().showTables()).split("\n")[1:-1] ]
pp.pprint(results)

for table in results:
  print oauth_client.query(SQL().select(int(table[0]), None, None))

# Start interaction with Smashrun
# Using some awesome login action and this handy JSON endpoint:
# http://smashrun.com/services/running-jsonservice.asmx
f = open('smashrun_secret')
try:
  smashrun_secret = f.readline().rstrip()
finally:
  f.close()
url = "http://smashrun.com/services/user-jsonservice.asmx/LoginUser"
body = '{"loginEmail":"smashrun.hardwarehank@ralree.com","loginPassword":"%s"}' % (smashrun_secret)
headers = {
            'Content-Type': 'application/json; charset=UTF-8',
            'Referer': 'http://smashrun.com/login',
          }
http = httplib2.Http()
response, content = http.request(url, 'POST', headers=headers, body=body)
pp.pprint(response)
pp.pprint(content)

headers['Cookie'] = response['set-cookie']
del headers['Referer']

url = "http://smashrun.com/services/running-jsonservice.asmx/SaveRunListItem"
body = '{"runListItem": { "distance":"2.71", "bookedUnitCode":"m", "startDateTime":"2012-01-19T06:32:00", "duration":7384000, "runId":null }}'
response, content = http.request(url, 'POST', headers=headers, body=body)
pp.pprint(response)
pp.pprint(content)
