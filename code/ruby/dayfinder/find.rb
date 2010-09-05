# Finds how many people were executed on each day of the week
require 'csv'
require 'time'

class CSVExamResults
  attr_accessor :days
  def initialize(filename)  
    @filename = filename  
    @days = {}
    @results = CSV.read(@filename)  
    @results.each do |res|
      t = Time.parse(res[0])
      @days[t.wday].nil? ? @days[t.wday] = 1 : @days[t.wday] += 1
    end
    @days
  end  
end  
    
c1 = CSVExamResults.new("death_penalty.csv")
c1.days.each do |k,v|
  puts Time::RFC2822_DAY_NAME[k]+": "+v.to_s
end
