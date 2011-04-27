# A super fast to write/think about hash table

def hashfun(key)
  hv = 0
  key.to_s.each_char do |x|
    hv += x.ord
  end
  hv *= key.size
  hv /= 73
  return hv
end
 
class Element
  attr_accessor :key, :value

  def initialize(key, value)
    @key = key
    @value = value
  end

  def print
    puts "#{@key}: #{@value||"NULL"}"
  end
end

class Table
  def find(key)
    hash = hashfun(key)
    e = @storage[hash]
    if e.key != key
      return nil
    end
    return e
  end

  def insert(key, value = nil)
    e = Element.new(key, value)
    # Need to store the key for collision resolution
    # calculate hash
    hash = hashfun(key)
    @storage[hash] = e
    # Make sure we don't have a collision
  end

  def delete(key)
  end

  def initialize
    @storage = []
  end
end

t = Table.new
t.insert("foo", "bar")
t.insert("bar", "baz")
t.insert("h")          # No value, so nil

e = t.find("foo")
e.print if !e.nil?
e = t.find("bar")
e.print if !e.nil?
e = t.find("h")
if !e.nil?
  e.print
else
  puts "NULL"
end

e = t.find("baz")
if !e.nil?
  e.print
else
  puts "NULL"
end
