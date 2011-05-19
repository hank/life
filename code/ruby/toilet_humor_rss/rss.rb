require 'rubygems'
require 'open-uri'
require 'hpricot'
require 'rss/maker'

version = "2.0"
destination = ENV['HOME']+"/public_html/toilet_humor.xml"
#destination = "th.xml"

content = RSS::Maker.make(version) do |m|
  m.channel.title = "Toilet Humor RSS Feed"
  m.channel.link = "http://www.ralree.info/toilet_humor.xml"
  m.channel.description = "Toilet Humor comic strip"
  m.items.do_sort = true

  doc = Hpricot(open('http://www.norbertech.com/archive/archive.html').read)
  (doc/"p[a]").each do |ptag|
    (ptag/"a").each do |atag|
      i = m.items.new_item
      date, i.title = atag.inner_html.split(" - ")
      i.link = "http://www.norbertech.com/archive/"+atag['href']
      i.date = Time.parse(date.gsub(/\./, "/"))
    end
  end
end

File.open(destination, "w") do |f|
  f.write(content)
end
