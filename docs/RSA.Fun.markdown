#RSA in your head
The following example of RSA is easy enough to do in your head.
##Key Generation
* Pick 2 primes `p` and `q`

<code>
p = 2, q = 5
</code>

* Calculate the modulus `n`

<code>
    n = pq = 10
<code>

* Calculate the totient `z`

<code>
    z = (p-1)(q-1) = 1*4 = 4
<code>

* Choose a prime `k` such that `k` is coprime to `z`.

<code>
    k = 3
<code>

* Our public key is:

<code>
    n = 10, k = 3
<code>

* Calculate the secret key

<code>
    kj = 1 (mod z)
    3j = 1 (mod 4)
    j = 3 # 9/4 has remainder 1
<code>

* Our secret key is:

<code>
    j = 3
<code>

##Encryption
* Encrypt the message:

<code>
    P = 2 (message), E = encrypted result
    n = 10, k = 3
    P^k = E (mod n)
    2^3 = E (mod 10)
    8 = E (mod 10)
    E = 8
<code>

##Decryption
* Decrypt the message

<code>
    E = 8, j = 3, n = 10
    E^j = P (mod n)
    8^3 = P (mod 10)
    8^3 = 2^9 = 512
    512 = P (mod 10) # 512/10 has remainder 2
    P = 2
<code>
 
##References
* [The RSA Algorithm Explained Using Simple Pencil and Paper Method](http://sergematovic.tripod.com/rsa1.html)
* [Wikipedia: RSA](http://en.wikipedia.org/wiki/RSA)
