# Return all nodes at a given level LTR
class Node
    attr_accessor :left, :right
    def initialize(val, left=nil, right=nil)
        @left = left
        @right = right
        @val = val
    end

    def print
      puts @val
    end
end

=begin
      f
     / \
    d   e
   /
  c
 / \
a  b
=end

a = Node.new("a")
b = Node.new("b")
c = Node.new("c", a, b)
d = Node.new("d", c)
e = Node.new("e")
f = Node.new("f", d, e)

def ltr(node, level)
  if node.nil? || level.nil?
    return nil
  end
  # Traverse left to the level
  if level == 1
    # Reached level, print
    node.print
  else
    ltr(node.left, level - 1)
    ltr(node.right, level - 1)
  end
end

=begin
Expected output for 1: f
                    2: de
                    3: c
                    4: ab
=end
(1..4).each do |i|
    puts "Level #{i}"
    ltr(f, i)
end
