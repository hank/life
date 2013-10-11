import binascii, hashlib
import argparse
b58_digits = '123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz'

parser = argparse.ArgumentParser()
parser.add_argument('key')
parser.add_argument('--tocustom', 
                    nargs=1, 
                    help="Custom version.  Use 2 hex chars.  Not compatible with other options")
parser.add_argument('--toltc', action="store_true", help="Convert input to LTC private key")
parser.add_argument('--toftc', action="store_true", help="Convert input to FTC private key")
parser.add_argument('--tobtc', action="store_true", help="Convert input to BTC private key")
args = parser.parse_args()

if args.toltc:
    args.version = "B0"
elif args.toftc:
    args.version = "8E"
elif args.tobtc:
    args.version = "80"
elif args.tocustom:
    args.version = args.tocustom[0]

def base58_encode(n):
    l = []
    while n > 0:
        n, r = divmod(n, 58)
        l.insert(0,(b58_digits[r]))
    return ''.join(l)

def base58_decode(s):
    n = 0
    for ch in s:
        n *= 58
        digit = b58_digits.index(ch)
        n += digit
    return n

def packl(lnum, padmultiple=1):
    if lnum == 0:
        return b'\0' * padmultiple
    elif lnum < 0:
        raise ValueError("Can only convert non-negative numbers.")
    s = hex(lnum)[2:]
    s = s.rstrip('L')
    if len(s) & 1:
        s = '0' + s
    s = binascii.unhexlify(s)
    if (padmultiple != 1) and (padmultiple != 0):
        filled_so_far = len(s) % padmultiple
        if filled_so_far != 0:
            s = b'\0' * (padmultiple - filled_so_far) + s
    return s

def unpackl(bytestr):
    return int(binascii.hexlify(bytestr), 16) if len(bytestr) > 0 else 0
 
def hexprint(s):
    for i in s:
        print "%02X" % (ord(i)),
    print

def numtowif(numpriv):
 step1 = args.version+hex(numpriv)[2:].strip('L').zfill(64)
 step2 = hashlib.sha256(binascii.unhexlify(step1)).hexdigest()
 step3 = hashlib.sha256(binascii.unhexlify(step2)).hexdigest()
 step4 = int(step1 + step3[:8] , 16)
 print hex(step4)
 return ''.join([b58_digits[step4/(58**l)%58] for l in range(100)])[::-1].lstrip('1')

def wiftonum(wifpriv):
 return sum([b58_digits.index(wifpriv[::-1][l])*(58**l) for l in range(len(wifpriv))])/(2**32)%(2**256)

def validwif(wifpriv):
 return numtowif(wiftonum(wifpriv))==wifpriv
print "Known input:", known_input
num = wiftonum(known_input)
print "Num:",
hexprint(packl(num))
print "WIF:",
wif = numtowif(num)
print wif
print "WIF Decode:",
hexprint(packl(wiftonum(wif)))
print "B58 decoded:",
hexprint(packl(base58_decode(wif)))


print "Input: ", args.key
decoded = wiftonum(args.key)
print "Input: ", hex(decoded)
binstr = packl(decoded)
print "Input: ", 
hexprint(binstr)
print "Output:",
hexprint(binstr)
new_key = unpackl(binstr)
wif = numtowif(decoded)
print "Output:", wif
