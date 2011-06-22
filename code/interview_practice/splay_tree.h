#include <utility>
#include <queue>
#include <cstdio>
#include <iostream>

template<class Key, class T>
struct splay_tree
{
  // Forward declarations
  private:
  struct node;
  public:

  splay_tree()
  : size(0)
  , root(NULL)
  {}

  splay_tree(const std::vector<std::pair<Key, T> >& init_vector)
  : size(0)
  , root(NULL)
  {
    // Initialize with the given values
    initialize(init_vector);
  }

  void initialize(const std::vector<std::pair<Key, T> >& init_vector)
  {
    typename std::vector<std::pair<Key, T> >::const_iterator it = init_vector.begin();
    if(!this->size == 0) empty(this->root);
    while(it != init_vector.end())
    {
      insert(*it++);
    }
  }

  ~splay_tree()
  {
    // Delete all elements in the tree
  }

  void empty(node* n)
  {
    puts("Empty");
    if(!n) return;
    free(n);
    for(int i = 0; i < 2; ++i) empty(n->children[i]);
  }

  T* find(const Key& k)
  {
    node* cur = this->root;
    while(cur)
    {
      if(cur->k > k) cur = cur->children[0];
      else if(cur->k < k) cur = cur->children[1];
      else break; // Found it!
    }
    if(cur) {
      splay(cur);
      return &cur->v;
    }
    else return NULL;
  }

  void print()
  {
    // BFS with preorder printing
    typedef std::pair<const node*, int> qp;
    std::queue<qp> q;
    if(this->root) q.push(qp(this->root, 0));
    int tracker = 0;
    while(!q.empty())
    {
      qp pt = q.front();
      q.pop();
      if(tracker < pt.second) { puts(""); ++tracker; }
      if(pt.first) {
        pt.first->print();
        q.push(qp(pt.first->children[0], pt.second + 1));
        q.push(qp(pt.first->children[1], pt.second + 1));
      }
      else {
        // Gotta print the nulls, dude
        printf("{N}");
      }
      if(tracker == 0) { puts(""); ++tracker; }
      else printf("   ");
    }
    puts(""); puts("");
  }

  bool insert(const std::pair<Key, T>& item)
  {
    if(!this->root) {
      this->root = new node(item);
      return true;
    }
    node* parent, * cur = root;
    do {
      parent = cur;
      if(item.first > cur->k) cur = cur->children[1];
      else if(item.second < cur->k) cur = cur->children[0];
      else { // We found a dupe
        break;
      }
    } while(cur);
    // Parent pointer should now point to our lovely parent.
    // Add a child
    node* childnode = new node(item);
    parent->addChild(childnode);
    splay(childnode);
    return true;
    // Could return false on duplicate kv-pair insert
  }

/*
  bool remove(const Key& k)
  {
  }
*/
  private:
    void splay(node* n)
    {
      // Root
      if(n == this->root) return;
      // Zig
      if(n->parent == this->root)
      {
        n->parent->rotate(n);
        this->root = n;
      }
      // Zig-Zig 
      else if(n->zigzig()) { 
        n->parent->parent->rotate(n->parent); 
        n->parent->rotate(n); 
        if(!n->parent) this->root = n;
      }
      else if(n->zigzag()) {
        n->parent->rotate(n); 
        n->parent->rotate(n); 
        if(!n->parent) this->root = n;
      }

      // Recurse!
      splay(n);
    }

    struct node
    {
      node(const std::pair<Key, T>& item)
      : k(item.first)
      , v(item.second)
      , parent(NULL)
      {
        this->children = {0};
      }

      void print() const
      {
        std::cout << "{" << k << ", " << v << "}";
      }

      // Returns whether we're parent's left or right child
      int pidx() 
      { return this == this->parent->children[0] ? 0 : 1; }
      // Returns whether parent is grandparent's left or right child
      int gpidx() 
      { return this->parent == this->parent->parent->children[0] ? 0 : 1; }

      bool zigzag()
      {
        // Are we a right child of a left child
        //     or a left child of a right child?
        if(!this->parent || !this->parent->parent) return false;
        if(gpidx() != pidx()) return true;
        else return false;
      }

      bool zigzig()
      {
        // Are we a right child of a right child
        //     or a left child of a left child?
        if(!this->parent || !this->parent->parent) return false;
        if(gpidx() == pidx()) return true;
        else return false;
      }

      void rotate(node* child)
      {
        int cidx = child == this->children[0] ? 0 : 1;   // Left, for example
        if(this->parent) {
          int px = pidx();
          this->parent->children[px] = child;            // Replace this in parent with
        }                                                // Child
        
        child->parent = this->parent;
        this->parent = child;
        this->children[cidx] = child->children[!cidx];   // My left subtree is now
        child->children[!cidx] = this;                   // childs old right subtree
      }                                                  // and I'm childs new right

      void addChild(node* child)
      {
        if(child->k < this->k) this->children[0] = child;
        else this->children[1] = child;
        child->parent = this;
      }

      Key k;
      T   v;
      node* parent;
      node* children[2];
    };

  size_t size;
  node* root;
};

