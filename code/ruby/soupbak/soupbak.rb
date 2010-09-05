#!/usr/bin/env ruby
require 'net/http'
require 'fileutils'
require 'rss/1.0'
require 'rss/2.0'
require 'open-uri'

require 'irb'

module IRB # :nodoc:
  def self.start_session(binding)
    unless @__initialized
      args = ARGV
      ARGV.replace(ARGV.dup)
      IRB.setup(nil)
      ARGV.replace(args)
      @__initialized = true
    end

    workspace = WorkSpace.new(binding)

    irb = Irb.new(workspace)

    @CONF[:IRB_RC].call(irb.context) if @CONF[:IRB_RC]
    @CONF[:MAIN_CONTEXT] = irb.context

    catch(:IRB_EXIT) do
      irb.eval_input
    end
  end
end

puts <<EOWOW
Welcome to the fantabulous Soup Backup Machine!
EOWOW

source = "current.rss"
content = ""
open(source) do |s| content = s.read end
outfile = File.new("index.html", "w")
begin
  FileUtils.mkdir 'assets'
rescue Errno::EEXIST
end
puts "Parsing input rss..."
rss = RSS::Parser.parse(content, false)

outfile.puts <<EOF
<html>
  <head>
    <title>#{rss.channel.title}</title>
  </head>
  <body>
    <h1>#{rss.channel.title}</h1>
    <p>#{rss.items.size} Items</p>
EOF

rss.items.each do |item|
  puts "Getting #{item.title}..."
  unless item.enclosure.nil?
      #IRB.start_session(Kernel.binding)
      url = URI.parse(item.enclosure.url)
      req = Net::HTTP::Get.new(url.path)
      res = Net::HTTP.start(url.host, url.port) do |http|
        http.request(req)
      end
      url.path =~ /.*\/(.*?)$/
      targetfile = $1
      if targetfile.nil?
        puts "Failed to parse #{item.enclosure}"
        next
      end
      open("assets/"+targetfile, "wb") { |file|
        file.write(res.body)
      }
  end
  desc = item.description.gsub(/http:\/\/asset\.soup\.io\/.*\//, '')
  outfile.puts <<EOF
<h3>#{item.title}</h3>
<p>
    #{desc}
</p>
EOF
end
