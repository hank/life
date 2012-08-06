import os
import random
import hashlib
 
BASE58 = '123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz'

 
def Candidate():
    """
    Generate a random, well-formed mini private key.
    """
    rgen = random.SystemRandom() # Good random.
    return('%s%s' % ('S', ''.join(
        [BASE58[ rgen.randrange(0,len(BASE58)) ] for i in range(21)])))
 
def GenerateKeys(numKeys = 10):
    """
    Generate mini private keys and output the mini key as well as the full
    private key. numKeys is The number of keys to generate, and 
    """
    keysGenerated = 0
    totalCandidates = 0
    while keysGenerated < numKeys:
        try:
            cand = Candidate()
            # Do typo check
            t = '%s?' % cand
            # Take one round of SHA256
            candHash = hashlib.sha256(t).digest()
            # Check if the first eight bits of the hash are 0
            if candHash[0] == '\x00':
                privateKey = GetPrivateKey(cand)
                print('\n%s\nSHA256( ): %s\nsha256(?): %s' %
                      (cand, privateKey, 
                       candHash.encode('hex_codec')))
                if CheckShortKey(cand):
                    print('Validated.')
                    # Generate QRCode
                    os.system('qrencode -o /tmp/test.png -s 50 -l H -m 6 %s' % (cand))
                    os.system('composite -gravity center coin.png /tmp/test.png %s.png' % (cand))
                else:
                    print('Invalid!')
                keysGenerated += 1
            totalCandidates += 1
        except KeyboardInterrupt:
            break
    print('\n%s: %i\n%s: %i\n%s: %.1f' %
          ('Keys Generated', keysGenerated,
           'Total Candidates', totalCandidates,
           'Reject Percentage', 100*(1.0-keysGenerated/float(totalCandidates))))
 
def GetPrivateKey(shortKey):
    """
    Returns the hexadecimal representation of the private key corresponding
    to the given short key.
    """
    if CheckShortKey(shortKey):
        return hashlib.sha256(shortKey).hexdigest()
    else:
        print('Typo detected in private key!')
        return None
 
def CheckShortKey(shortKey):
    """
    Checks for typos in the short key.
    """
    if len(shortKey) != 22:
        return False
    t = '%s?' % shortKey
    tHash = hashlib.sha256(t).digest()
    # Check to see that first byte is \x00
    if tHash[0] == '\x00':
        return True
    return False

GenerateKeys()
