#include <stdio.h>
#include <stdlib.h>
struct bin_tree_n {
  struct bin_tree_n* left;
  struct bin_tree_n* right;
  int data;
  int count;
};

struct bin_tree {
  struct bin_tree_n* root;
};

struct bin_tree_n* node_init(int data)
{
  struct bin_tree_n* node = calloc(1, sizeof(struct bin_tree_n));
  node->data = data;
  node->count = 0;
  return node;
}

int tree_height_inner(struct bin_tree_n* node)
{
  if(!node) return 0; // Leaf
  int left_h = tree_height_inner(node->left) + 1;
  int right_h = tree_height_inner(node->right) + 1;
  return left_h > right_h ? left_h : right_h;
}

int tree_height(struct bin_tree* bt)
{
  return tree_height_inner(bt->root);
}

void insert(struct bin_tree* bt, int data)
{
  struct bin_tree_n* node = bt->root, *tmp;
  if(!node) {
    puts("Init root");
    bt->root = node_init(data);
    return;
  }
  while(node) {
    printf("Now at %d\n", node->data);
    if(node->left &&
       node->left->data > data) {
      puts("Going left");
      node = node->left;
    }
    else if(node->right &&
       node->right->data < data) {
      puts("Going Right");
      node = node->right;
    }
    else break;
  }
  if(data > node->data) {
    printf("%d is > %d\n", data, node->data);
    if(!node->right) node->right = node_init(data);
    else {
      tmp = node->right;
      node->right = node_init(data);
      node->right->right = tmp;
    }
  } else if(data < node->data) {
    printf("%d is < %d\n", data, node->data);
    if(!node->left) node->left = node_init(data);
    else {
      tmp = node->left;
      node->left = node_init(data);
      node->left->left = tmp;
    }
  } else { // Equals
    printf("%d == %d\n", node->data, data);
    ++node->count;
  }
}

void free_tree_inner(struct bin_tree_n* node)
{
  if(!node) return;
  struct bin_tree_n* left = node->left, * right = node->right;
  printf("Freeing %p {%p %p %d %d}\n", node, node->left, node->right,
      node->data, node->count); fflush(stdout);
  free(node);
  free_tree_inner(left);
  free_tree_inner(right);
}

void free_tree(struct bin_tree* bt)
{
  free_tree_inner(bt->root);
}

int main() {
  struct bin_tree b = {0};
  insert(&b, 5);
  insert(&b, 9);
  insert(&b, 11);
  insert(&b, 3);
  insert(&b, 2);
  insert(&b, 0);
  insert(&b, 1);
  insert(&b, 4);
  printf("Tree Height is %d\n", tree_height(&b));
  free_tree(&b);
  return 0;
}
