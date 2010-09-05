require "rubygems"
require "net/dns/packet"

f = File.open("ACCOUNT")
user, pin = f.gets.split(" ")
f.close
packet = Net::DNS::Packet.new("bip.com")

txt = Net::DNS::Question.new("#{user}.#{pin}.So.Far.TwitDNS.is.limited.to.63.Chars", Net::DNS::TXT)
packet.question = txt
s = UDPSocket.new
s.bind(nil, 19000)
s.send(packet.data, 0, "127.0.0.1", 5454)
