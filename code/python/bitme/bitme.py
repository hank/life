from urllib import urlencode
import requests, json, base64
import hmac, hashlib
from collections import OrderedDict
from datetime import datetime
import bitme_internal
API_URLROOT = 'https://bitme.com/rest'
class BitmeAPI:
    def __init__(self, apikey, apisecret=None):
        self.apikey = apikey
        self.apisecret = base64.b64decode(apisecret)

    def query(self, url, params={}, auth=False):
        # Generate nonce (UTC timestamp since epoch works)
        nonce = bitme_internal.datetime_to_timestamp(
                datetime.now()) * 1000 + 1000000000
        params = OrderedDict({'nonce': nonce})
        p_encoded = urlencode(params)
        mac = base64.b64encode(
                hmac.new(self.apisecret, p_encoded, hashlib.sha512).digest())
        url = API_URLROOT + url
        headers = {'Rest-Key': self.apikey,
                   'Rest-Sign': mac}
        r = requests.get(url, params=params, headers=headers)
        return r.json()

    def verify_credentials(self):
        return self.query('/verify-credentials', auth=True)
    def accounts(self):
        return self.query('/accounts', auth=True)
    def bitcoin_address(self):
        return self.query('/bitcoin-address', auth=True)

if __name__ == '__main__':
    import argparse, logging, pprint
    pp = pprint.PrettyPrinter(indent=4)
    parser = argparse.ArgumentParser(description="Bitme API")
    parser.add_argument('--apikeyfile',
                        default='APIKEY',
                        help="The file containing the API key (not the secret!)")
    parser.add_argument('--apisecretfile',
                        help="The file containing the api secret.  if unspecified, access to privileged api calls will not be possible.")
    parser.add_argument('--loglevel',
                        default='INFO',
                        help="Set log level [INFO, DEBUG, etc.]")
    args = parser.parse_args()
    logging.basicConfig(format='%(asctime)s %(message)s',
                        level=args.loglevel)
    API_KEY = None
    try:
        with open(args.apikeyfile, 'r') as f:
            API_KEY = f.read().strip()
    except IOError as e:
        logging.info("Error opening file '{}'.  Make sure it exists and contains your key.".format(args.apikeyfile))
        raise e
    logging.info('API Key: ' + API_KEY)

    # If we were given an API secret, use it
    API_SECRET = None
    if args.apisecretfile:
        try:
            with open(args.apisecretfile, 'r') as f:
                API_SECRET = f.read().strip()
        except IOError as e:
            logging.info("Error opening file '{}'.  Make sure it exists and contains your key.".format(args.apisecretfile))
            raise e

    # Create new API instance
    api = BitmeAPI(API_KEY, API_SECRET)
    response = api.verify_credentials()
    pp.pprint(response)
    response = api.accounts()
    pp.pprint(response)
    response = api.bitcoin_address()
    pp.pprint(response)
