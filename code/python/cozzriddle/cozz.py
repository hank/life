import binascii
def caesar(plaintext,shift):
  alphabet=["a","b","c","d","e","f","g","h","i","j","k","l",
  "m","n","o","p","q","r","s","t","u","v","w","x","y","z"]
  dic={}
  for i in range(0,len(alphabet)):
    dic[alphabet[i]]=alphabet[(i+shift)%len(alphabet)]
  ciphertext=""
  for l in plaintext.lower():
    if l in dic:
      l=dic[l]
    ciphertext+=l
  return ciphertext
# My ...
name = "cozz"

# Once I made a journey and visited some of my old friends.
# The first one is a doctor and he has 5 children (MD5)
# He lives in a very beautiful house.
# The house always impresses me so much that I drive 5 rounds around it before
# actually ringing the bell (while eating his meals)
# The only problem with this friend is that he uses pepper instead of salt
# to all his meals
import hashlib
m = binascii.b2a_hex(hashlib.md5(name+"pepper").digest())
m = binascii.b2a_hex(hashlib.md5(m+"pepper").digest())
m = binascii.b2a_hex(hashlib.md5(m+"pepper").digest())
m = binascii.b2a_hex(hashlib.md5(m+"pepper").digest())
m = binascii.b2a_hex(hashlib.md5(m+"pepper").digest())
print "After 5xmd5 = ", m

# The funny thing is after eating there you feel like your stomach has grown
# about 137% of the original size.
import base64
m = base64.b64encode(m)
print "After base64 = ", m

# The trip went on to Maryland.  Sadly, the friend I was going to visit there
# wasn't at home.  But accidentally I met a friend of this friend who also
# wanted to visit him.  After all the only thing I can say about this friend of
# the friend is that he literally is a stupid or unpleasant person (git).
# git -> sha1
m = binascii.b2a_hex(hashlib.sha1(m).digest())
print "After sha1 = ", binascii.b2a_hex(m)

# As the trip was more expensive than I thought, I decided to step by at one of
# my richer friends and ask for some money. I dont even know which country he
# is really from, but his name sounds like japanese.
# Satoshi -> 2xsha256
m = hashlib.sha256(binascii.b2a_hex(hashlib.sha256(m).digest())).digest()
print "After 2xsha256 = ", binascii.b2a_hex(m)

# Having filled up my wallet I could no afford a flight to europe.
# Of course for that I had to make some money exchange.
# I simply exchanged all my numbered coins I had and became on 500euro note
# Which fit very well at the end of my wallet.
# (remove all numbers from hash, put "500euro" at the end
import re
m = re.sub(r'[0-9]', '', binascii.b2a_hex(m)) + "500euro"
print "After 'cashing in' numbers = ", m

# The friend I visited in europe looks so old I always make fun of him
# that he must be born before jesus.  Whenever possible he tells me his war
# stories and how some fat guy kicked his ass.
# Caesar
m = caesar(m, 26)
print "After Caesar = ", m

# I even met a woman in europe.  Her name was alice.  She invited me to her
# house.  I was great she even had a whirlpool there.  Immediately we both
# jumped into it.  The neighbours already shouting cozz+alice didn't really
# bother me at this time. (whirlpool hash)
import whirlpool
m = m + "alice"
for _ in xrange(50): m = whirlpool.hash(m)
print "Whirlpool = ", binascii.b2a_hex(m)

# When I had to get back to america I was looking for my flight number 888 at
# the airport, but I couldnt find it anywhere.  So I called another friend in
# europe and asked him for advice. He has won his first race championship in
# 1996 in europe driving with a speed of 160 miles per hour.   This friend now
# guided me really really quickly until I found my flight back home. Funny
# thing was that my flight number was at the very beginning of the airport.
ripe = m
while ripe[0:3] != "888":
  ripe = hashlib.new('ripemd160', ripe).hexdigest()
print "Ripe result = ", ripe

# Over all this was a very exciting trip, and the whole trip I never felt like I
# had to add another entering somewhere.  
# (no carriage returns / newlines)

# The only thing that bothers me is that I have lost alice phone number
# somewhere. Only thing I can remember it was an eight digit number starting
# with 78.  Well at least I know where I can find her.
# (append 78xxxxxx (x=0-9) to the result until key is found)
