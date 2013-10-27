# Bitme Python API
## Requirements
* requests library (pip install requests)

## Usage
Take a look at example.py.  This shows how to use the accounts API call to
list your accounts.  It also shows how you can store your API information in
files (to prevent it getting into committed code).

    hank@crow$ python example.py 
    {u'accounts': [{u'currency_name': u'Bitcoin', 
     u'available': u'0.06979500000000000000', u'currency_cd': u'BTC', 
     u'balance': u'0.06979500000000000000'}, 
     {u'currency_name': u'Litecoin', u'available': u'0.00000000000000000000', 
      u'currency_cd': u'LTC', u'balance': u'95.00000000000000000000'}]}

