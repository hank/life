#!/usr/bin/env python
import sys, time, os, re
# apt-get install python-bs4 python-mechanize
from mechanize import Browser
from bs4 import BeautifulSoup

LOGIN_URL = 'http://www.bitminter.com/login'

br = Browser()
br.set_handle_robots(False)
br.open(LOGIN_URL)
br.select_form(nr=1)
br['openid_username'] = "ralree"
br['openid_identifier'] = "http://ralree.myopenid.com/"
resp = br.submit()            # Submit the form
print "OpenID form submitted"

br.select_form(name="openid-form-redirection")
resp = br.submit()            # Submit the form
print "OpenID redirection submitted"

br.select_form(nr=0)
br['password'] = open('pw').readline().rstrip()
resp = br.submit()            # Submit the form
print "OpenID provider form submitted"

resp = br.open('https://bitminter.com/members/transactions')
payset = set()
print "Latest paid BTC transactions (streaming):"
while True:
  page = resp.read()
  soup = BeautifulSoup(page)

  # Find all the payments listed on the page
  payments = map(lambda x: [x.find_next_sibling().text, 
                            x.find_parent().find_next_siblings()[1].text,
                            x.find_parent().find_previous_sibling().text], 
		 soup.find_all(text=re.compile("Payment")))
  payments.reverse()
  for i in payments:
    if re.search('BTC', i[1]) and i[2] not in payset:
      print "\t", i[2], i[0]+":", i[1]
      payset.add(i[2])
  time.sleep(120)
  resp = br.reload()
