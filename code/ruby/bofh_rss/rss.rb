require 'rubygems'
require 'time'
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
  (doc/'div[@class="spurious"]/div').each do |div|
    next if not div['class'] =~ /story-ref/
    atag = (div/'a')[0]
    i = m.items.new_item
    i.title = atag.inner_html.gsub(/<abbr.*<\/abbr>/, 'BOFH')
    i.link = "http://www.theregister.co.uk"+atag['href']
    if((div/'span[@class="date"]').inner_html =~ /(\d+).*?(\w+) (\d+):(\d+)/)
      # No year given, get it from URL
      day = $1
      month = $2
      hour = $3
      minute = $4
      atag['href'] =~ /.*\/(\d{4})\/(\d{2})\/(\d{2}).*/
      year = $1
      i.date = Time.utc(year, month.downcase, day, hour, minute)
    else 
      i.date = Time.parse((div/'span[@class="date"]').inner_html)
    end
    i.description = (div/'p[@class="standfirst"]').inner_html
  end
end

File.open(destination, "w") do |f|
  f.write(content)
end
