#include <stdio.h>

struct jsw_node {
  int red;
  int data;
  struct jsw_node* link[2];
};

struct jsw_tree {
  struct jsw_node* root;
};

static inline int is_red(struct jsw_node* root)
{
  return root && root->red == 1;
}

struct jsw_node* jsw_single(struct jsw_node* root, int dir)
{
  struct jsw_node* save = root->link[!dir];
  root->link[!dir] = save->link[dir];
  save->link[dir] = root;

  root->red = 1;
  save->red = 0;

  return save;
}

struct jsw_node* jsw_double(struct jsw_node* root, int dir)
{
  root->link[!dir] = jsw_single(root->link[!dir], !dir);
  return jsw_single(root, dir);
}

int jsw_rb_assert(struct jsw_node* root)
{
  int lh, rh;

  if(!root)
  {
    return 1;
  }
  struct jsw_node* ln = root->link[0];
  struct jsw_node* rn = root->link[1];

  if(is_red(root))
  {
    if(is_red(ln) || is_red(rn))
    {
      puts("Red Violation");
      return 0;
    }
  }

  lh = jsw_rb_assert(ln);
  rh = jsw_rb_assert(rn);

  if((ln && ln->data >= root->data) ||
      rn && rn->data <= root->data) 
  {
    puts("Binary Tree Violation");
    return 0;
  }

  if(lh != 0 && rh != 0 && lh != rh)
  {
    puts("Black violation");
    return 0; 
  }

  if(lh != 0 && rh != 0)
    return is_red(root) ? lh : lh + 1;
  else
    return 0;
}

struct jsw_node* make_node(int data)
{
  struct jsw_node *rn = calloc(1, sizeof(struct jsw_node));
  if(rn)
  {
    rn->data = data;
    rn->red = 1;
  }
  return rn;
}


