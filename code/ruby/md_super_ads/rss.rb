require 'rubygems'
require 'open-uri'
require 'hpricot'
require 'rss/maker'

version = "2.0"
destination = ENV['HOME']+"/public_html/md_super_ads.xml"

content = RSS::Maker.make(version) do |m|
  m.channel.title = "MD Super Ads Classifieds RSS"
  m.channel.link = "http://www.ralree.info/md_super_ads.xml"
  m.channel.description = "MD Super ads has good deals!"
  m.items.do_sort = true

  doc = Hpricot(open('http://www.marylandsuperads.com/items_for_sale_Classifieds/index.aspx').read)
  (doc/'div[@class=item]').each do |item|
    # For every anchor that isn't an image...
      i = m.items.new_item
      i.title = (item/'span[@class=itemTitle]/a').inner_html
      i.link = "http://www.marylandsuperads.com"+(item/'span[@class=itemTitle]/a')[-1]['href']
      begin
      i.date = Time.parse(((item/'div[@class=description]/table/tr/td')[-1]/'div').inner_html.gsub(/.*&nbsp;(.*)/, '\1').strip+" 12:00")
      rescue
      e.date = Time.now
      end
      i.description = (item/'div[@class=description]').inner_html
  end
end

File.open(destination, "w") do |f|
  f.write(content)
end
