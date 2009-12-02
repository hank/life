#!/usr/bin/env ruby
#GiganticLumber: Import Key
#Imports a key given in the query string.
require 'gpgme'
require 'cgi'
require 'lumber_support'

cgi = CGI.new("html4")
buf = ""

$target_id = nil

# Check if we have a POST
if cgi.request_method !~ /POST/
  buf += "<p><b>Usage:</b> POST with key=&lt;keyid&gt;</p>"
  render_buf(cgi, buf)
  exit
else
  # We have a POST!


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
  signer_id = cgi['signer_id']
  data1 = GPGME::Data.from_str(cgi['key'])

  # Strip 0x from signer ID
  signer_id.gsub!(/^0x/i, '')
  # Check validity
  if signer_id.size != 8 and signer_id.size != 16
    buf += <<EOWOW
<p>Invalid Signer Key ID.  Formatting like any of the following will do:</p>
<ul>
  <li>F693F0F246C171A0</li>
  <li>46C171A0</li>
  <li>0xF693F0F246C171A0</li>
  <li>0x46C171A0</li>
</ul>
EOWOW
    render_buf(cgi, buf)
    exit
  end

  # Import the key
  ctx.import(data1)
  import_result = ctx.import_result()
  if import_result.considered == 0
    buf += "<p>Key not found.</p>"
    render_buf(cgi, buf)
    exit
  end
  buf += "<p>Key #{import_result.imports[0].fpr} Imported</p>"

  # Grab the key from the keyring, and start processing
  key = ctx.get_key(import_result.imports[0].fpr)
  if key.uids.size == 0
    buf += "<p>No UIDs found.  Please check key</p>"
    render_buf(cgi, buf)
    exit
  end

  primary_email = key.uids[0].email

  # Parse the key sigs
  # Make sure we found that the key is somewhat signed
  begin
    buf += key_with_sigs(key, signer_id)
  rescue RuntimeError
    buf += <<EOOMG
<h3>Hmmm...</h3>
<p>It seems that the key ID you gave me has never signed the key you uploaded.
Please try again</p>
EOOMG
    render_buf(cgi, buf)
    exit
  end

  # Give the use an offer they can't refuse.
  buf += <<EOOMG
<h3>Does this look correct?</h3>
<p>If not, hit your browser's back button and try again.</p>
<p>If it does look alright, put in your email and you'll be
notified when the other party reciprocates.
We'll also notify the other party via their primary email (#{primary_email}).</p>
<form method="post" action="save_exchange.rb">
  <label>Email</label>
  <input type="text" name="signer_email" />
  <input type="text" name="signee_email" value="#{primary_email}"/>
  <input type="text" name="signer_key" value="#{$target_id}"/>
  <input type="text" name="signee_key" value="#{key.subkeys[0].keyid}"/>
  <input type="submit" value="Notify Me" />
</form>
EOOMG
  render_buf(cgi, buf);
end
