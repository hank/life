import requests
from BeautifulSoup import BeautifulSoup
import dns.resolver
req = requests.get('https://www.privateinternetaccess.com/pages/network/')
soup = BeautifulSoup(req.text)
tds = soup.findAll('td', attrs={'data-label':'Hostname'})
reso = dns.resolver.Resolver()
reso.nameservers = ['8.8.8.8', '8.8.4.4']
for td in tds:
    print td.text + ":"
    answers = reso.query(td.text, "A")
    for rdata in answers:
        print "\t" + str(rdata)
