require 'rubygems'
require 'open-uri'
require 'hpricot'
require 'rss/maker'

version = "2.0"
destination = "mdshooters_classifieds.xml"

content = RSS::Maker.make(version) do |m|
  m.channel.title = "MDShooters Classifieds RSS"
  m.channel.link = "http://www.ralree.info/mdshooters_classifieds.xml"
  m.channel.description = "MDShooters Classifieds live so you can snipe."
  m.items.do_sort = true

  doc = Hpricot(open('http://mdshooters.com/vbclassified.php').read)
  (doc/'a').each do |a|
    # For every anchor that isn't an image...
    if a['href'] =~ /vbclassified.*do=ad/ and not a.inner_html =~ /<img/
      i = m.items.new_item
      i.title = a.inner_html
      i.link = "http://www.mdshooters.com/"+a['href']
      i.date = Time.parse((a.parent/'div[@class=time]/span').inner_html.gsub('-', '/')+" 12:00")
    end
  end
end

File.open(destination, "w") do |f|
  f.write(content)
end
