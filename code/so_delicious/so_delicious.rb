#!/usr/bin/env ruby
require 'open3'
require 'cgi'
require 'rexml/document'
require 'sqlite3'

wget = "wget"
wget_options = []
wget_options.push("-e robots=off")
wget_options.push("--user-agent=\"Mozilla/5.0 (X11; U; Linux; fr; rv:1.9.0.6) Gecko/2009011913 Firefox/3.0.6\""); 
wget_options.push("-P cache -t2 -pkHE -R mpeg,mpg,avi,mov")

puts "So Delicious.."
begin
file = File.open("myDelicious.xml")
doc = REXML::Document.new(file)
db = SQLite3::Database.new("delicious.db")
db.execute("CREATE TABLE IF NOT EXISTS bookmarks (
              id INTEGER PRIMARY KEY,
              link varchar(1024),
              name varchar(255),
              local_url varchar(1024),
              time DATE
              )")
db.execute("CREATE TABLE IF NOT EXISTS tags (
              id INTEGER PRIMARY KEY,
              name varchar(64)
              )")
db.execute("CREATE TABLE IF NOT EXISTS taggings (
              bid INTEGER,
              tid INTEGER
              )")
rescue
  puts "Error: #{$!}"
  puts "Please fix this."
  exit
end

doc.elements.each("posts/post") do |post|
   rows = db.execute( "SELECT * FROM bookmarks WHERE link=?", post.attributes['href'] )
   if rows.size == 0
     puts "Downloading "+post.attributes['description']
     cmd = "#{wget} #{wget_options.join(" ")} \"#{post.attributes['href']}\""
     #puts "Running: #{cmd}"
     filename = ""
     Open3.popen3(cmd) do |stdin, stdout, stderr|
       err = stderr.read
       err =~ /Saving to: `(.*)\/(.*?)'$/
       next if $1.nil?
       path = $1
       filename = path + '/' + CGI.escape($2)
       #puts "SAVED TO: #{filename}"
     end

     # Do bookmark
     db.execute( "INSERT INTO bookmarks VALUES (NULL,?,?,?,?)", post.attributes['href'], post.attributes['description'], filename, post.attributes['time'])
     rows = db.execute( "SELECT * FROM bookmarks WHERE link=?", post.attributes['href'] )
     bid = rows[0][0]

     # Do tags
     post.attributes['tag'].split(" ").each do |tag|
       #print "#{tag} "
       tag.gsub("\"","")
       rows = db.execute( "SELECT * FROM tags WHERE name=?", tag)
       if rows.size == 0
         db.execute( "INSERT INTO tags VALUES (NULL,?)", tag)
         rows = db.execute( "SELECT * FROM tags WHERE name=?", tag)
       end
       tid = rows[0][0]

       rows = db.execute( "SELECT * FROM taggings WHERE bid=? and tid=?", bid, tid)
       # Make Relationship
       if rows.size == 0
         db.execute( "INSERT INTO taggings VALUES (?,?)", bid, tid)
       end
     end
   else
     puts "Already have #{post.attributes['description']}"
   end
end

