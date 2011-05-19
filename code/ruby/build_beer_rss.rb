#!/usr/bin/env ruby
require 'md5'
require 'rubygems'
require 'hpricot'
require 'open-uri'
require 'builder'

# Get the document to scrape
doc = Hpricot(open("http://beeradvocate.com/user/beer_reviews?ba=ralree"))
trs = (doc/"#mainContent"/"table")[0].search("tr")

# Create the feed
target = File.new("/home/ralreein/public_html/beer/beer.xml", "w")
xml = Builder::XmlMarkup.new(:target => target, :indent => 1)
xml.instruct! 
xml.feed "xmlns" => "http://www.w3.org/2005/Atom" do
  xml.id "http://www.ralree.info/beer/beer.xml"
  xml.title "ralree the BeerAdvocate"
  xml.subtitle "Recent Beer Reviews"
  xml.link  "rel" => "self", "href" => "http://www.ralree.info/beer/beer.xml"
  xml.updated Time.now.iso8601
  xml.author  { xml.name "Erik Gregg"; xml.email "ralree@gmail.com" }

  # For each TR, make an entry
  trs.each_with_index do |a,i|
    tds = a.search("td").to_a
    if tds.length == 7 and not (tds[0]/"text()").to_s =~ /Date/
      xml.entry do
        # Review Date + 5PM
        time = Time.parse(tds[0].inner_html.gsub('-', '/')) + 1700
        xml.id "tag:ralreebeeradvocate,#{time.strftime("%Y-%m-%d")}:#{MD5.new((tds[1]/"a")[0]["href"])}"
        xml.updated(time.iso8601)
        xml.title((tds[1]/"text()").join(" "))
        xml.link(:href => 
          ("http://www.beeradvocate.com" + ((tds[1]/"a")[0]["href"])),
          :title => (tds[1]/"text()").to_s)
        xml.summary do |p|
          p.text! <<EOOMFG
    Brewery: #{(tds[2]/"a")[0].inner_html}
    Style: #{(tds[3]/"a")[0].inner_html}
    Serving: #{tds[4].inner_html}
    ABV: #{tds[5]/"text()"}
    Rating: #{(tds[6]/"b").inner_html}
EOOMFG
        end
      end
    end
  end
end
