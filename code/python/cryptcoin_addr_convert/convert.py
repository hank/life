import hashlib
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('key')
parser.add_argument('--tocustom', nargs=1, help="Custom version.  Use 2 hex chars.  Not compatible with other options")
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


__b58chars = '123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz'
__b58base = len(__b58chars)

def b58encode(v):
	long_value = int(v.encode("hex_codec"), 16)
	result = ''
	while long_value >= __b58base:
		div, mod = divmod(long_value, __b58base)
		result = __b58chars[mod] + result
		long_value = div
	result = __b58chars[long_value] + result
	# Bitcoin does a little leading-zero-compression:
	# leading 0-bytes in the input become leading-1s
	nPad = 0
	for c in v:
		if c == '\0': nPad += 1
		else: break
	return (__b58chars[0]*nPad) + result

def b58decode(v):
	long_value = 0L
	for (i, c) in enumerate(v[::-1]):
		long_value += __b58chars.find(c) * (__b58base**i)
	result = ''
	while long_value >= 256:
		div, mod = divmod(long_value, 256)
		result = chr(mod) + result
		long_value = div
	result = chr(long_value) + result
	nPad = 0
	for c in v:
		if c == __b58chars[0]: nPad += 1
		else: break
	result = chr(0)*nPad + result
	return result

def numtowif(numpriv):
	step1 = args.version+numpriv
	step2 = hashlib.sha256(step1).hexdigest()
	step3 = hashlib.sha256(step2).hexdigest()
	step4 = step1 + step3[:8]
	step5 = b58encode(step4)
	return step5

def wiftonum(wifpriv):
	step1 = b58decode(wifpriv)
	step2 = step1[:-8]
	step3 = step2[2:]
	return step3

print(numtowif(wiftonum(args.key)))