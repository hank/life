# A super fast to write/think about hash table

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
    puts "hash for #{key} is #{hash}"
    return nil if @storage[hash].nil?
    # collisions...
    until !@storage[hash].nil? and @storage[hash].key == key
        hash = (hash + 1) % @storage.size
    end
    @storage[hash]
  end

  def insert(key, value = nil)
    e = Element.new(key, value)
    # Need to store the key for collision resolution
    # calculate hash
    hash = hashfun(key)
    # Make sure we don't have a collision
    # NOTE: this inf-loops when we're full, could keep a count..
    until @storage[hash].nil?
        hash = (hash + 1) % @storage.size
    end
    puts "inserting #{key} at #{hash}"
    @storage[hash] = e
  end

  def delete(key)
  end

  def initialize
    # Pre-allocate 1000 nils
    @storage = Array.new(1000)
  end

  # Knuth hash
  # Add up characters, multiply to defeat some character order
  # issues, then multiply result by itself + 3, then divide by m
  def hashfun(key)
    hv = 0
    key.to_s.each_char do |x|
      hv += x.ord
      hv *= 2
    end
    hv *= hv+3
    hv /= @storage.size
    # make sure we're smaller than m
    hv %= @storage.size
    return hv
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
