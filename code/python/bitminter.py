import sys, time, os
from mechanize import Browser

LOGIN_URL = 'http://www.bitminter.com/login'

br = Browser()
br.set_handle_robots(False)
br.open(LOGIN_URL)
br.select_form(nr=1)
br['openid_username'] = "ralree"
br['openid_identifier'] = "http://ralree.myopenid.com/"
resp = br.submit()            # Submit the form
print resp.read()
br.select_form(name="openid-form-redirection")
resp = br.submit()            # Submit the form
print resp.read()

br.select_form(nr=0)
br['password'] = open('pw').readline().rstrip()
resp = br.submit()            # Submit the form

print resp.read()
