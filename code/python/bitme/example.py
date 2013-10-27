from bitme import BitmeAPI

# Read keys
with open('APIKEY', 'r') as f:
    API_KEY = f.read().strip()
with open('APISECRET', 'r') as f:
    API_SECRET = f.read().strip()

api = BitmeAPI(API_KEY, API_SECRET)
print api.accounts()
