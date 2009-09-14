require 'rubygems'
require 'open-uri'
require 'hpricot'
require 'rss/maker'

version = "2.0"
destination = ENV['HOME']+"/public_html/bofh.xml"
#destination = "bofh.xml"

content = RSS::Maker.make(version) do |m|
  m.channel.title = "BOFH Feed from the Register"
  m.channel.link = "http://www.ralree.info/bofh.xml"
  m.channel.description = "Bastard Operator From Hell RSS feed from The Register"
  m.items.do_sort = true

  doc = Hpricot(open('http://www.theregister.co.uk/odds/bofh/').read)
  (doc/'div[@class="story-ref"]').each do |div|
    atag = div/'a'
    i = m.items.new_item
    i.title = atag.inner_html
    i.link = "http://www.theregister.co.uk"+atag[0]['href']
    i.date = Time.parse((div/'span[@class="date"]').inner_html)
    i.description = (div/'p[@class="standfirst"]').inner_html
  end
end

File.open(destination, "w") do |f|
  f.write(content)
end
