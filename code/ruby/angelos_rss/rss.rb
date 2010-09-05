require 'rubygems'
require 'open-uri'
require 'hpricot'
require 'rss/maker'

version = "2.0"
destination = ENV['HOME']+"/public_html/angelos.xml"
#destination = "angelos.xml"

content = RSS::Maker.make(version) do |m|
  m.channel.title = "Angelos Keromytis Paper Feed"
  m.channel.link = "http://www.ralree.info/angelos.xml"
  m.channel.description = "Angelos Keromytis' Papers scraped from his site, on tap"
  #m.items.do_sort = true

  doc = Hpricot(open('http://www1.cs.columbia.edu/~angelos/cv.html').read)
  (doc/'#journalpubs/ol/li').each do |pub|
    i = m.items.new_item
    begin
      i.title = (pub/'dl/dt').inner_text.gsub(/\r|\n/m, ' ').gsub(/"/, '')
      i.description = pub.inner_html
      i.link = "http://www1.cs.columbia.edu/~angelos/"+(pub/'dl/dt/i/a')[0]['href'] if (pub/'dl/dt/i/a')[0]
      i.date = Time.now
    end
  end
end

File.open(destination, "w") do |f|
  f.write(content)
end
