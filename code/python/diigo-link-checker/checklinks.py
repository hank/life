import urllib2, socket, logging, urllib
from argparse import ArgumentParser
from pydiigo import DiigoApi
from getpass import getpass
from query_yes_no import query_yes_no
logging.basicConfig(level=logging.INFO)

LINKSCHECKER_APIKEY='14e08f106e144265'

# Fool silly websites by lying to them
hdr = {'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.10; rv:40.0) Gecko/20100101 Firefox/40.0'}

parser = ArgumentParser(description='Find and remove dead links from your Diigo bookmarks')
parser.add_argument('--user', metavar='USER', help='Diigo username', required=True)
parser.add_argument('--passwordfile', metavar='FILE', help='Diigo Password File')
parser.add_argument('--offset', type=int, metavar='OFFSET', default=0, help='Offset into all bookmarks to start')

args = parser.parse_args()

if args.passwordfile:
    with open(args.passwordfile, 'r') as f:
        pw = f.read().rstrip()
else:
    pw = getpass('Diigo Password')

#print "Password: {}".format(repr(pw))

api = DiigoApi(
        user=args.user,
        password=pw,
        apikey=LINKSCHECKER_APIKEY)

# Get lists of bookmarks to process, public and private
offset = args.offset
while True:
    print "::: Fetching 100 bookmarks, offset {}".format(offset)
    bookmarks = api.bookmarks_find(
        user=args.user, 
        rows=100, 
        filter='all',
        start=offset)
    if len(bookmarks) == 0:
        print "All done!"
        break
    for bookmark in bookmarks:
        try:
            sanitized_url = urllib.quote_plus(bookmark.url, safe='/:#&?=')
        except:
            print "Could not sanitize URL"
            continue
        print u"Attempting to open {}".format(sanitized_url)
        error_occurred = False
        try:
            req = urllib2.Request(sanitized_url,headers=hdr)
            resp = urllib2.urlopen(req, timeout=30)
        except urllib2.HTTPError as e:
            print 'HTTP Error requesting: {}'.format(e)
            error_occurred = True
        except urllib2.URLError as e:
            print 'URL Error requesting: {}'.format(e)
            error_occurred = True
        except socket.error as e:
            print 'Socket Error requesting: {}'.format(e)
            error_occurred = True
        responsecode = resp.getcode()
        if responsecode != 200: 
            print 'Unexpected HTTP response: {}'.format(responsecode)
            error_occurred = True
        # Logic to deal with broken links
        if error_occurred:
            shoulddelete = query_yes_no("Delete?", default="no")
            if shoulddelete:
                # Tell Diigo to delete the link
                result = api.bookmark_delete(url=bookmark.url)
                print result['message']
    offset += 100
