#include <cstdio>
using namespace std;

struct tree_node
{
  tree_node(int val)
  : data(val)
  , balance(0)
  {
    link[0] = link[1] = NULL;
  }
  
  int data;
  int balance;
  struct tree_node* link[2];
};

struct tree
{
  tree()
  : root(NULL)
  {}

  bool insert(int val)
  {
    if(!this->root)
    {
      this->root = new tree_node(val);
      return true;
    }
    int dir = val > root->data;
    insert_r(val, root->link[dir]);
  }

  bool insert_r(int val, tree_node* cur_node)
  {
    if(!cur_node) return false;
    if(val < cur_node->data) 
      return insert_r(val, cur_node->link[0]);
    else if(val < cur_node->data) 
      return insert_r(val, cur_node->link[1]);
    else return false;
  }
  private:
  tree_node* root;
};

int main()
{
  return 0;
}
