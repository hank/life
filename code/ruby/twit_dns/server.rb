require 'rubygems'
require 'net/dns/packet'
require 'net/dns/question'
require 'socket'
require 'oauth'
require 'twitter'
require 'sqlite3'

# Change the 
class Net::DNS::RR::TXT
  def build_pack
    str = [@txt.length,@txt].pack("C a*")
    @txt_pack = str
    @rdlength = @txt_pack.size
  end
end


class DNSTwitter
  def initialize
    @db = SQLite3::Database.new("accounts.db")
    @db.execute("CREATE TABLE IF NOT EXISTS users (
       id INTEGER PRIMARY KEY,
       name varchar(255) UNIQUE,
       pin varchar(255),
       access_token varchar(255),
       access_secret varchar(255)
       )")

    @db.execute("CREATE TABLE IF NOT EXISTS request_tokens (
       id INTEGER PRIMARY KEY,
       request_token varchar(255),
       request_secret varchar(255),
       time datetime
       )")

    f = File.open("CREDENTIALS")
    key = f.gets.chomp; secret = f.gets.chomp
    f.close
    @oauth = Twitter::OAuth.new(key, secret)
  end

  # Clean up expired tokens.  Expiration is 15 minutes.
  def clean_tokens
    @db.execute("DELETE FROM request_tokens WHERE strftime('%s','now') - strftime('%s',time) > 900")
  end

  # Returns a request_token object
  # Stores the secret in a hash for later use
  def generate_request
    token = @oauth.consumer.get_request_token
    begin
    @db.execute( "INSERT INTO request_tokens VALUES (NULL,?,?,current_timestamp)",
      token.token, token.secret)
    rescue
      puts "Failed to insert request token #{$!}"
      return false
    end
    token
  end

  # Auths the user and stores them in the database on success.
  def authorize(req_token, given_num)
    # Clean up tokens
    #clean_tokens()
    begin
    rows = @db.execute("SELECT * FROM request_tokens WHERE request_token=?", req_token)
    rescue
      puts "Failed to find request token: #{$!}"
      return false
    end
    req_secret = rows[0][2]
    begin
      puts "Authorizing #{req_token} #{req_secret} #{given_num}"
      @oauth.authorize_from_request(req_token, req_secret, given_num)
    rescue
      puts "Failed to authorize user #{$!}"
      return false
    end
    # If it works, save off the data.
    puts "OMFG it works."
    acct = Twitter::Base.new(@oauth)
    begin
    profile = acct.verify_credentials
    @db.execute( "INSERT INTO users VALUES (NULL,?,?,?,?)",
      profile.name, given_num, @oauth.access_token.token, @oauth.access_token.secret)
    rescue Exception => e
      if e.class == SQLite3::SQLException 
        # We already have this user!
        puts "User #{profile.name} already has credentials"
      else
        puts "Failed to insert user #{profile.name}: #{$!}, #{e.class}"
        return false
      end
    end
    acct
  end

  # Function to obtain a client who's already registered.
  def get_client(name, pin)
    # Find a user and print his details
    rows = @db.execute( "SELECT * FROM users WHERE name=? and pin=?", name, pin)
    if rows.size == 0
      # User not found.  Ask them to auth
      puts "You should really authorize, #{name}"
      return false
    end
    begin
    @oauth.authorize_from_access(rows[0][3], rows[0][4])
    rescue
      puts "Failed to authorize user #{name}: #{$!}"
      return false
    end
    Twitter::Base.new(@oauth)
  end
end

class UDPServer
  def initialize(port)
    @port = port
    @dt = DNSTwitter.new
  end

  def start
    @socket = UDPSocket.new
    @socket.bind(nil, @port)
    while true
      packet = @socket.recvfrom(1500)
      dpacket = Net::DNS::Packet::parse(packet)
      ip = packet[1][3]
      port = packet[1][1]
      dpacket.question.each do |q|
        # I have you now!
        case q.qType.to_s
          when "A" then
            # Generates a request
            puts "A: "+q.qName
            req_token = @dt.generate_request
            txt = Net::DNS::RR.new("#{q.qName} IN TXT Goto:#{req_token.authorize_url}")
            dpacket.answer = txt
            @socket.send(dpacket.data, 0, ip, port)
            puts "Goto:#{req_token.authorize_url}"
          when "CNAME" then
            # Authorizes a user with a pin
            begin
              pin, token = q.qName.split('.')[0..2]
              acct = @dt.authorize(token, pin)
              if acct == false
                puts "Authentication Failed in a good way"
                next
              end
            rescue
              puts "Authentication Failed: #{$!}"
              next
            end
            profile = acct.verify_credentials
            txt = Net::DNS::RR.new("#{q.qName} IN TXT Authenticated as #{profile.name}")
            dpacket.answer = txt
            @socket.send(dpacket.data, 0, ip, port)
          when "MX" then
            # Check a user's status
            user = q.qName.split('.')[0]
            begin
              status = Twitter.user(user).status.text
              txt = Net::DNS::RR.new(
                "#{q.qName} IN TXT #{user}'s status: #{status}")
            rescue
              puts "Failed to get status for #{user}: #{$!}"
              txt = Net::DNS::RR.new(
                "#{q.qName} IN TXT Unable to get #{user}'s status")
            end
            dpacket.answer = txt
            @socket.send(dpacket.data, 0, ip, port)
          when "TXT" then
            # Post!
            a = q.qName =~ /^(\w+)\.(\d+)\.(.*)/
            if a.nil?
              txt = Net::DNS::RR.new(
                "#{q.qName} IN TXT ERROR: Format is <TwitterUsername>.<Pin>.<Message.dot.delimited>")
              dpacket.answer = txt
              txt = Net::DNS::RR.new(
                "#{q.qName} IN TXT For Example: bob.123456.This.is.my.message")
              dpacket.answer = txt
              @socket.send(dpacket.data, 0, ip, port)
              next
            end
            user = $1; pin = $2; message = $3.gsub(/\./, " ")
            txt = Net::DNS::RR.new("#{q.qName} IN TXT Posting: "+user+" "+pin+" "+message)
            dpacket.answer = txt
            @socket.send(dpacket.data, 0, ip, port)
            puts "Posting: "+user+" "+pin+" "+message
            begin
              client = @dt.get_client(user, pin)
              if client == false
                puts "Unable to post, client failed."
                txt = Net::DNS::RR.new("#{q.qName} IN TXT ERROR: Failed to find your account.  Register?")
                dpacket.answer = txt
                @socket.send(dpacket.data, 0, ip, port)
                next
              end
              client.update(message)
            rescue
              puts "Error while posting: #{$!}"
            end
          else puts "Unknown Question Type #{q.qType.class}"
        end
      end
    end
  end
end

# Start DNS Server
server = UDPServer.new(5454)
server.start
