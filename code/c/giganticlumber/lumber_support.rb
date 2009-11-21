def key_with_sigs(key, signer_id)
  target_id = nil
  buf = "<ul>"
  key.uids.each do |uid|
    next if uid.signatures.size == 0
    next if uid.revoked? or uid.invalid?
    my_sigs = uid.signatures.select {|v| v.keyid =~ /#{signer_id}$/}
    next if my_sigs.size == 0
    # Now we have a set of our signatures on the UID
    buf += "<li>#{uid.name}"
    buf += " &lt;#{uid.email}&gt;" if uid.email.size != 0
    buf += " (#{uid.comment})" if uid.comment.size != 0
    buf += "<ul>"
    my_sigs.each do |sig|
      buf += "<li>"
      # Print the signature information itself
=begin
      buf += case sig.sig_class
        when 0x10 then "Generic Level "
        when 0x11 then "<span style=\"color: #880000;\">Persona Level</span> "
        when 0x12 then "<span style=\"color: #000088;\">Casual Level</span> "
        when 0x13 then "<span style=\"color: #008800;\">Positive Level</span> "
      end
=end
      # Check all kinds of nastiness
      buf += "<b>Revoked</b> " if sig.revoked?
      buf += "<b>Expired</b> " if sig.expired?
      buf += "<b>Invalid</b> " if sig.invalid?
      buf += "<b>Non-exportable</b> " if not sig.exportable?
      buf += "Signature "

      # Print timestamp information, only if valid
      if sig.timestamp.to_i != 0 && sig.timestamp.to_i != -1
        buf += "Made on #{sig.timestamp.to_s}"
      end
      if sig.expires.to_i != 0
        buf += "Expires on #{sig.expires.to_s}"
      end
      target_id = sig.keyid if target_id.nil?
      buf += "</li>"
    end
    buf += "</ul>"
    buf += "</li>"
  end
  buf += "</ul>"
  if target_id.nil?
    # We didn't find any signatures
    raise RuntimeError 
  end
  return buf
end

def render_buf(cgi, buf)
  cgi.out {
    cgi.html {
      cgi.body {
        buf
      }
    }
  }
end
