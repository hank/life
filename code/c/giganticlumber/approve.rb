#!/usr/bin/env ruby
#GiganticLumber: Import Key
#Imports a key given in the query string.
require 'rubygems'
require 'sqlite3'
require 'gpgme'
require 'cgi'
require 'lumber_support'

cgi = CGI.new("html4")
buf = ""


# Check if we have a POST
if cgi.request_method !~ /GET/
  buf += "<p><b>Usage:</b> GET with ex=&lt;exchangeid&gt;</p>"
  render_buf(cgi, buf)
  exit
else
  # We have a GET!

  GPGME.engine_check_version(GPGME::GPGME_PROTOCOL_OpenPGP);
  GPGME.set_engine_info(GPGME::GPGME_PROTOCOL_OpenPGP,
        nil, 
        "/var/www/.gnupg"
  )
  # Make a GPG context
  ctx = GPGME::Ctx.new
  # Turn on signature parsing
  ctx.keylist_mode = GPGME::GPGME_KEYLIST_MODE_SIGS


  # Get data
  id = cgi['ex']
  db = SQLite3::Database.new('/tmp/keyex.db')
  begin
    result = db.get_first_row("SELECT signer_key, signee_key, 
        signer_email, signee_email
        FROM key_exchanges
        WHERE id = ?
    ", id)
  rescue SQLite3::Exception => e
    buf += "<p>Error finding your exchange.  Please email support.</p>"
    buf += "<pre>Code #{e.code}: #{e}</pre>"
    render_buf(cgi, buf)
    exit
  end

  signer_key, signee_key, signer_email, signee_email = result
  buf += "<h1>Key Exchange Verification</h1>"
  buf += "<p><b>Key #{signer_key} (#{signer_email}) has signed key #{signee_key} (#{signee_email}).</b></p>"
  buf += "<p>The owner of key #{signee_key} must verify that the following signatures are correct and up to his/her standards.  Any issues should be directed to the signer (#{signer_email})</p>"

  # Grab the key from the keyring, and start processing
  key = ctx.get_key(signee_key)
  if key.uids.size == 0
    buf += "<p>Error Reading Key: No UIDs found.</p>"
    render_buf(cgi, buf)
    exit
  end

  # Print the key with the signatures for the signer
  begin
    buf += key_with_sigs(key, signer_key)
  rescue RuntimeError
    # No signatures.  Fail!
    buf += "<p>Weird error parsing key: it appears key #{signer_key} never signed
           key #{signee_key}<p>"
    render_buf(cgi, buf)
    exit
  end

  # Give the use an offer they can't refuse.
  buf += <<EOOMG
<h3>Does this look correct?</h3>
<p>If it does look alright, clearsign the following text and paste the result in the box:

<pre>Yes, I approve of this key exchange with {#{signer_key}}</pre>

<p>The result should look something like this:</p>

<pre>
-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA1

Yes, I approve of this key exchange with {F693F0F246C171A0}
-----BEGIN PGP SIGNATURE-----
Version: GnuPG v1.4.9 (GNU/Linux)

iEYEARECAAYFAksHVMQACgkQ9pPw8kbBcaA8IQCeLeTMnVbrLzsO/gEz/JH6+5x/
JbAAn1ygauZJFxbg6TB3rK1IAr9fFKSF
=te5b
-----END PGP SIGNATURE-----
</pre>

<p>If you're using GnuPG, you can use the following command:</p>

<pre>gpg --clearsign <<< "Yes, I approve of this key exchange with {#{signer_key}}"</pre>

<p>It's a good practice to run it through signature verification before submitting.  One can use <code>gpg --verify</code> for this.</p>

<form method="post" action="verify.rb">
  <label>Signed Text</label><br />
  <textarea cols=78 rows=9 name="clearsign"></textarea>
  <input type="submit" value="Submit" />
</form>
EOOMG
  render_buf(cgi, buf);
end
