#!/usr/bin/env ruby
require 'rubygems'
require 'cgi'
require 'sqlite3'
require 'tmail'
require 'net/smtp'
require 'lumber_support'

cgi = CGI.new("html4")

signer_key = cgi["signer_key"]
signee_key = cgi["signee_key"]
signer_email = cgi["signer_email"]
signee_email = cgi["signee_email"]

buf = ""
db = SQLite3::Database.new('/tmp/keyex.db')

# Create the schema if we need to
db.execute('CREATE TABLE IF NOT EXISTS key_exchanges (
  id INTEGER PRIMARY KEY, 
  signer_key STRING, 
  signee_key STRING,
  signer_email STRING,
  signee_email STRING,
  signer_approval INTEGER DEFAULT 0,
  signee_approval INTEGER DEFAULT 0,
  UNIQUE (signer_key, signee_key))'
)

# Save exchange to the database
link_prefix = get_cgi_link_prefix()
begin
  result = db.execute(
    "INSERT INTO key_exchanges 
    (signer_key, signee_key, signer_email, signee_email)
    VALUES (?, ?, ?, ?)",
    signer_key, signee_key, signer_email, signee_email
  )
rescue SQLite3::SQLException => e
  if e.code == 1
    buf += "<p>You have already initiated this exchange.</p>"
    result = db.get_first_value(
      "SELECT id FROM key_exchanges 
         WHERE signer_key = ? AND
               signee_key = ?",
        signer_key, signee_key
    )
    buf += "<p>Go <a href=\"approve.rb?ex=#{result}\">here</a> to see the status.</p>"
  else # wtf...
    buf += "<p>Sorry pal.  Something went wrong and failed all over itself in the tater base:</p>"
    buf += "<pre>Code #{e.code}: #{e}</pre>"
  end
  render_buf(cgi, buf);
  exit
end

# Get our ID
id = db.get_first_value(
    "SELECT id FROM key_exchanges 
    WHERE signer_key = ? AND
    signee_key = ?",
    signer_key, signee_key
)


# Construct the emails
# Signer Email
mail1 = TMail::Mail.new
mail1.to = signer_email
mail1.from = "root@localhost"
mail1.subject = "GiganticLumber Key Exchange: Key ID #{signee_key}"
mail1.date = Time.now
mail1.body = <<EOMAIL
The key exchange with the owner of the key with the fingerprint #{signee_key}
has begun.  You must now wait until they sign and submit your key here:

#{link_prefix}approve.rb?ex=#{id}

Once that happens, we'll send you a link and you can verify the validity of
their signatures on your key UIDs.  Once both of you signify that you're
satisfied with the signing of your respective keys, the signed keys will be
emailed to each of you simultaneously.
EOMAIL

# Signee Email
mail2 = TMail::Mail.new
mail2.to = signee_email
mail2.from = "root@localhost"
mail2.subject = "GiganticLumber Key Exchange: Key ID #{signer_key}"
mail2.date = Time.now
mail2.body = <<EOMAIL
The owner of the key with the fingerprint #{signer_key} has initiated a key
exchange.  To complete the exchange, verify their signature here:

#{link_prefix}approve.rb?ex=#{id}

Sign their key with your key (#{signee_key}) and submit it.  Once that happens,
we'll send the other party a link and you can verify the validity of your
signatures on their key UIDs.  Once both of you signify that you're satisfied
with the signing of your respective keys, the signed keys will be emailed to
each of you simultaneously.
EOMAIL


if result
  Net::SMTP.start('localhost', 25 ) do|smtp|
    smtp.send_message(
      mail1.to_s,
      'root@ralree.dyndns.org',
      signer_email
    )
    smtp.send_message(
      mail2.to_s,
      'root@ralree.dyndns.org',
      signee_email
    )
  end
  buf += "<p>Thanks.  We'll let you know when the other party responds.</p>"
  buf += "<p>Go <a href=\"approve.rb?ex=#{id}\">here</a> to see the status.</p>"
else
  buf += "<p>Sorry pal.  Something went wrong and failed all over itself in the tater base:</p>"
  buf += "<pre>#{db.errmsg}</pre>"
end
render_buf(cgi, buf);
