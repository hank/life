# Various traversals
class Node
    attr_accessor :left, :right
    def initialize(val, left=nil, right=nil)
        @left = left
        @right = right
        @val = val
    end

    def to_s
      @val
    end
end

=begin
      e
     / \
    d   f
   /
  b
 / \
a  c
=end

a = Node.new("a")
c = Node.new("c")
b = Node.new("b", a, c)
d = Node.new("d", b)
f = Node.new("f")
e = Node.new("e", d, f)

# inorder traversal
# just takes a node
def inorder(n)
  if !n.left.nil?  # Print left subtree
    inorder(n.left)
  end
  print n.to_s, ", " # Print self
  if !n.right.nil?
    inorder(n.right) # Print right subtree
  end
end

# preorder traversal
# just takes a node
def preorder(n)
  print n.to_s, ", " # Print self
  if !n.left.nil?  # Print left subtree
    preorder(n.left)
  end
  if !n.right.nil?
    preorder(n.right) # Print right subtree
  end
end

# postorder traversal
# just takes a node
def postorder(n)
  if !n.left.nil?  # Print left subtree
    postorder(n.left)
  end
  if !n.right.nil?
    postorder(n.right) # Print right subtree
  end
  print n.to_s, ", " # Print self
end

# levelorder traversal
# just takes a node
def levelorder(n)
  # Enqueue us
  a = [n]
  while !a.empty?
    b = a[0]
    a.delete_at(0)
    print b.to_s, ", "
    a.push(b.left) if !b.left.nil?
    a.push(b.right) if !b.right.nil?
  end
end

puts "Inorder traversal:"
inorder(e)
puts

puts "Preorder traversal"
preorder(e)
puts

puts "Postorder traversal"
postorder(e)
puts

puts "Levelorder traversal"
levelorder(e)
puts
