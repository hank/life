require 'rubygems'
require 'open-uri'
require 'hpricot'
require 'rss/maker'

version = "2.0"
destination = ENV['HOME']+"/public_html/badassotw.xml"
#destination = "botw.xml"

content = RSS::Maker.make(version) do |m|
  m.channel.title = "Badass of the Week RSS Feed"
  m.channel.link = "http://www.ralree.info/badassotw.xml"
  m.channel.description = "Badass of the week posts about awesome people doing uber-awesome things.  Keep up."
  m.items.do_sort = true

  doc = Hpricot(open('http://www.badassoftheweek.com/list.html').read)
  (doc/"font[@size='+1']/a")[1..-1].each do |atag|
    next if atag.class == Hpricot::BogusETag
    i = m.items.new_item
    i.title = atag.inner_html
    i.link = "http://www.badassoftheweek.com/"+atag['href']
    i.date = Time.parse(atag.previous_node.to_s.gsub(/\r|\n|:.*| /, ''))
  end
end

File.open(destination, "w") do |f|
  f.write(content)
end
