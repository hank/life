#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
#define EDGE_MATRIX_WIDTH 20
#define NODE_MAX 15
struct graph
{
  ~graph()
  {
    // When graph goes down, free all nodes.
    vector<node*>::iterator p = this->nodes.begin();
    while(p != this->nodes.end())
    {
      delete (*p++);
    }
  }
  struct node
  {
    node(int data)
    : data(data)
    , visited(false)
    {}

    void add_edge(node* t)
    {
      edges.push_back(t);
    }

    void print() const
    {
      printf("%d {", data);
      vector<node*>::const_iterator p = this->edges.begin();
      if(p != this->edges.end())
      {
        for(;;)
        {
          printf("%d", (*p++)->data);
          if(p == this->edges.end()) break;
          printf(", ");
        }
      }
      printf("}\n");
    }

    int data;
    vector<node*> edges;
    bool visited; // For searching
  };

  void add_node(node* n)
  {
    this->nodes.push_back(n);
  }

  void bfs(node* n)
  {
    // First, make sure all the nodes are marked unvisited
    vector<node*>::const_iterator p = this->nodes.begin();
    while(p != this->nodes.end())
    {
      (*p++)->visited = false;
    }
    queue<node*> visit_q;
    visit_q.push(n);
    while(!visit_q.empty())
    {
      // For each node, push its neighbors onto the queue
      // and print the node, then process.
      node* e = visit_q.front();
      visit_q.pop();
      p = e->edges.begin();
      while(p != e->edges.end())
      {
        if(!(*p)->visited)
        {
          visit_q.push(*p);
          (*p)->visited = true;
        }
        ++p;
      }
      e->print();
    }
    
  }

  void print() const
  {
    vector<node*>::const_iterator p = this->nodes.begin();
    while(p != this->nodes.end())
    {
      (*p++)->print();
    }
  }

  vector<node *> nodes;
};

int main()
{
  graph g;
  graph::node* n = new graph::node(1);
  g.add_node(n); 
  n = new graph::node(2);
  g.add_node(n); 
  n = new graph::node(3);
  g.add_node(n); 
  n = new graph::node(4);
  g.add_node(n); 

  g.nodes[0]->add_edge(g.nodes[1]);
  g.nodes[2]->add_edge(g.nodes[3]);
  g.nodes[1]->add_edge(g.nodes[3]);
  g.nodes[3]->add_edge(g.nodes[1]);
  g.print();

  g.bfs(g.nodes[0]);
  return 0;
}
