import sys
sys.path.insert(0,'/home/hank/repos/discogs_client')
import discogs_client
from decimal import Decimal
try:
    with open("TOKEN", "r") as f:
        token = f.read().rstrip()
except IOError:
    print "Put your user token in the TOKEN file"
    sys.exit()
d = discogs_client.Client('DiscogsProfit/0.1', user_token=token)
me = d.identity()
collection_fields = me.collection_fields()

# Ensure we have a "Paid" field to use
matching_fields = [k for k in collection_fields if k['name'] == "Paid"]
if len(matching_fields) == 0:
    print "Failed to find Paid custom field. Make sure you make this and fill it in"
    print "Existing fields:", ", ".join([k['name'] for k in collection_fields])
    sys.exit()
else:
    paid_field = matching_fields[0]

paid_field_id = paid_field['id']

total_paid = Decimal(0)
# We have the paid field, query all releases to build total amount paid
for release in me.collection_folders[0].releases:
    paid_field = [k for k in release.notes if k['field_id'] == paid_field_id]
    if len(paid_field) != 0:
        paid_field = paid_field[0]
        # Add paid amount to total
        paid_amount = Decimal(paid_field['value'].strip('$'))
        total_paid += paid_amount
print "Total paid:", total_paid
print "Total value:", me.collection_value()
