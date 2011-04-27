# A super fast to write/think about hash table

def hashfun(key)
  hv = 0
  key.to_s.each do |x|
    hv = x
  end
  return hv
end
 
class Element
  attr_accessor :key, :value

  def initialize(key, value)
    @key = key
    @value = value
  end

  def print
    puts @key+": "+@value
  end
end

class Table
  def find(key)
  end

  def insert(key, value = nil)
    e = Element.new(key, value)
    # Need to store the key for collision resolution
    # calculate hash
    hash = hashfun(key)
    @storage[key] = e
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
e.print
