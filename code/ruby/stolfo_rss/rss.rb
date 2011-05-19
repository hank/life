require 'rubygems'
require 'open-uri'
require 'hpricot'
require 'rss/maker'

version = "2.0"
destination = ENV['HOME']+"/public_html/stolfo.xml"
#destination = "stolfo.xml"

content = RSS::Maker.make(version) do |m|
  m.channel.title = "Salvatore Stolfo Paper Feed"
  m.channel.link = "http://www.ralree.info/stolfo.xml"
  m.channel.description = "Salvatore Stolfo's Papers scraped from his site, on tap"
  #m.items.do_sort = true

  doc = Hpricot(open('http://ids.ftw.fm/Home/publications/documents').read)
  (doc/'table[@class="filecabinet-table"]/tbody/tr').each do |pub|
    i = m.items.new_item
    begin
      i.title = (pub/'td[@class="td-desc filecabinet-desc"]')[0].inner_text
      i.link = (pub/'td[@class="td-file"]/a')[0]['href']
      i.description = pub.inner_html
      i.date = Time.now
    end
  end
end

File.open(destination, "w") do |f|
  f.write(content)
end
