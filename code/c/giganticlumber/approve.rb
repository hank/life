#!/usr/bin/env ruby
#GiganticLumber: Approve
#Allows the signee to approve the signer's signatures on his/her key
require 'rubygems'
require 'sqlite3'
require 'gpgme'
require 'cgi'
require 'lumber_support'

cgi = CGI.new("html4")
buf = ""

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

# Check if we have a POST
if cgi.request_method !~ /GET/
  # A POST?!  Time to handle submission
  begin
    data1 = GPGME::Data.from_str(cgi['signed'])
    ctx.verify(data1)
  rescue GPGME::Error::NoData
    buf += "<p>Invalid signature.  Please clearsign with key #{signer_key} 
            and try again.</p>"
    render_buf(cgi, buf)
    exit
  end
  verify_result = ctx.verify_result
  if verify_result.signatures.empty?
    # Unsigned text
    buf += "<p>The text is unsigned.  It needs to be signed with the
            key bearing the fingerprint #{signer_key}.</p>"
    render_buf(cgi, buf)
    exit
  elsif verify_result.signatures[0].fpr !~ /#{signer_key}$/
    # This was signed with the wrong key
    buf += "<p>The text was signed with the wrong key 
            (#{verify_result.signatures[0].fpr}).  It needs to be signed with the
            key bearing the fingerprint #{signer_key}.</p>"
    render_buf(cgi, buf)
    exit
  elsif verify_result.signatures[0].summary != GPGME::SIGSUM_VALID && 
        verify_result.signatures[0].summary != GPGME::SIGSUM_GREEN
    # Invalid Signature
    status = case(verify_result.signatures[0].validity)
      when GPGME::SIGSUM_RED then "the signature as BAD"
      when GPGME::SIGSUM_KEY_REVOKED then "the key as revoked"
      when GPGME::SIGSUM_KEY_EXPIRED then "the key as expired"
      when GPGME::SIGSUM_SIG_EXPIRED then "the signature as expired"
      when GPGME::SIGSUM_KEY_MISSING then "the key for verification missing (did you sign with the right key)"
      else "an unspecified error (#{verify_result.signatures[0].validity})"+ CGI::escapeHTML("#{verify_result.inspect}")
    end
    buf += "<p>The signature is invalid.  GPG reports #{status}.
            It needs to be signed with the
            key bearing the fingerprint #{signer_key}.</p>"
    render_buf(cgi, buf)
    exit
  end
  # If we're here, we checked all our bases.
  begin
    db.execute("UPDATE key_exchanges
        SET signee_approval = 1
        WHERE id = ?
    ", id)
  rescue SQLite3::Exception => e
    buf += "<p>Error saving your exchange.  Please email support.</p>"
    buf += "<pre>Code #{e.code}: #{e}</pre>"
    render_buf(cgi, buf)
    exit
  end
  buf += "<p><b>Congratulations!</b>  You have completed your end of 
          the exchange!</p>"
  render_buf(cgi, buf)
else
  # We have a GET!

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

<form method="post" action="approve.rb">
  <label>Signed Text</label><br />
  <textarea cols=78 rows=9 name="signed"></textarea>
  <input type="hidden" name="ex" value="#{id}" />
  <input type="submit" value="Submit" />
</form>
EOOMG
  render_buf(cgi, buf);
end
