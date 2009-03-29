#!/usr/bin/env ruby
require 'rexml/document'
require 'sqlite3'

puts "So Delicious.."
begin
file = File.open("myDelicious.xml")
doc = REXML::Document.new(file)
db = SQLite3::Database.new("delicious.db")
db.execute("CREATE TABLE IF NOT EXISTS bookmarks (
              id INTEGER PRIMARY KEY,
              link varchar(1024),
              name varchar(255),
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
   post.attributes['href'] =~ /:\/\/(.*)/
   begin
     puts "Stat-ing #{$1}"
     File.stat($1)
     file_not_found = 0
   rescue
     file_not_found = 1
   end
   if rows.size == 0
     puts "Downloading "+post.attributes['description']
     `wget -R mov,avi -t 5 -pk "#{post.attributes['href']}"`

     # Do bookmark
     db.execute( "INSERT INTO bookmarks VALUES (NULL,?,?,?)", post.attributes['href'], post.attributes['description'], post.attributes['time'] )
     rows = db.execute( "SELECT * FROM bookmarks WHERE link=?", post.attributes['href'] )
     bid = rows[0][0]

     # Do tags
     post.attributes['tag'].split(" ").each do |tag|
       print "#{tag} "
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
     puts
   elsif file_not_found == 1
     # Only download.
     puts "Downloading "+post.attributes['description']
     `wget -r -l 1 "#{post.attributes['href']}"`
   else
     puts "Already have #{post.attributes['description']}"
   end
end

