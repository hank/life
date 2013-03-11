#!/usr/bin/env python

import os
import json
import urllib2
import datetime
import sys
from bs4 import BeautifulSoup

filepath = "prices.dat"
dataurl = "http://bitcoincharts.com/charts/chart.json?m=mtgoxUSD&SubmitButton=Draw&r=360&i=Daily&c=0&t=S&m1=10&m2=25&x=0&i1=&i2=&i3=&i4=&v=1&cv=0&ps=0&l=0&p=0&"
metalsdataurl = "http://services.packetizer.com/spotprices/?f=json"
#mtgoxtickerurl = "http://mtgox.com/api/0/data/ticker.php"

### BITCOIN

bcd = urllib2.urlopen(dataurl).read()

newprices = [ [datetime.datetime.utcfromtimestamp(row[0])] + [row[4]] for row in json.loads(bcd) ]
newprices = [ ("P", x.strftime("%Y/%m/%d %H:%M:%S"), "BTC", "$" + str(y)) for x,y in newprices ]
newprices = dict ( [ d[1] + " " + d[2], " ".join(d) ] for d in newprices )

#mtgox = urllib2.urlopen(mtgoxtickerurl).read()
#mtgox_json = json.loads(mtgox)
#last_bitcoin_price = mtgox_json["ticker"]["last"]
#date = datetime.datetime.now()
#newprices = ["P", date.strftime("%Y/%m/%d %H:%M:%S"), "BTC", "$%.8f"%last_bitcoin_price]
#newprices = {newprices[1] + " " + newprices[2]:" ".join(newprices)}

### METALS

metalscd = urllib2.urlopen(metalsdataurl).read()
metalscd = json.loads(metalscd)
date = metalscd["date"].replace("-","/") + " 17:00:00"
metalprices = [
  [ "P", date, "XAU",      "$" + metalscd["gold"]                     ],
  [ "P", date, "XAG",      "$" + metalscd["silver"]                   ],
  [ "P", date, "PAMPAU",   "$" + str(float(metalscd["gold"])   +  40) ],
  [ "P", date, "RCMPAU",   "$" + str(float(metalscd["gold"])   +  50) ],
  [ "P", date, "ROUNDSAG", "$" + str(float(metalscd["silver"]) + 1.5) ],
]
metalprices = dict( [ d[1] + " " + d[2], " ".join(d) ] for d in metalprices )

### LTC

btce_ltc = "http://www.cryptocoincharts.info/period-charts.php?period=alltime&resolution=day&pair=ltc-btc&market=btc-e"

soup = BeautifulSoup(urllib2.urlopen(btce_ltc))
tags = soup.find_all('tr')
ltcprices = dict()
for tag in tags:
  tds = tag.find_all('td')
  if len(list(tds)) != 6:
    continue
  date = tds[0].contents[0]
  close_price = tds[4].contents[0].split(" ")[0]
  ltcprices[date + " " + close_price] = " ".join(["P", date, "00:00:00", "LTC", "BTC", close_price])

### PPC

ppc_url = "http://www.cryptocoincharts.info/period-charts.php?period=alltime&resolution=day&pair=ppc-btc&market=ppcbitparking"

soup = BeautifulSoup(urllib2.urlopen(ppc_url))
tags = soup.find_all('tr')
ppcprices = dict()
for tag in tags:
  tds = tag.find_all('td')
  if len(list(tds)) != 6:
    continue
  date = tds[0].contents[0]
  close_price = tds[4].contents[0].split(" ")[0]
  ppcprices[date + " " + close_price] = " ".join(["P", date, "00:00:00", "PPC", "BTC", close_price])


concatdict = dict()
concatdict.update(newprices)
concatdict.update(metalprices)
concatdict.update(ltcprices)
concatdict.update(ppcprices)

values = sorted(concatdict.values())
string = "\n".join(values)
datafile = file(filepath,"w")
datafile.write(string)
datafile.flush()
