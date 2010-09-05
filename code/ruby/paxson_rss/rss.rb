require 'rubygems'
require 'open-uri'
require 'hpricot'
require 'rss/maker'

version = "2.0"
destination = ENV['HOME']+"/public_html/paxson.xml"
#destination = "paxson.xml"
$MONTHS="January|February|March|April|May|June|July|August|September|October|November|December"

content = RSS::Maker.make(version) do |m|
  m.channel.title = "Vern Paxson Paper Feed"
  m.channel.link = "http://www.ralree.info/paxson.xml"
  m.channel.description = "Vern Paxon's Papers scraped from his site, on tap"
  #m.items.do_sort = true

  doc = Hpricot(open('http://www.icir.org/vern/papers.html').read)
  (doc/'b/a')[0..-2].each do |atag|
    i = m.items.new_item
    begin
      next if not atag.inner_text
      i.title = atag.inner_text.gsub(/\r|\n/, "")
      i.description = atag.inner_html
      i.link = atag['href']
      tmp = atag.parent.next
      j = 0
      while not tmp.to_s =~ /#{$MONTHS}/ and j < 3 do
        tmp = tmp.next
        j += 1
      end
      if tmp.to_s =~ /#{$MONTHS}/
        i.date = Time.parse(tmp.to_s.gsub(/.*,/, ''))
      end
    rescue
      puts $!
      i.date = Time.now
    end
  end
end

File.open(destination, "w") do |f|
  f.write(content)
end
