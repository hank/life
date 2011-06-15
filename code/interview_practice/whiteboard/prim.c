#include <stdio.h>
#include <strings.h>

struct edge {
  int v1;
  int v2;
  int weight;
  int color;
};

void print_edge(struct edge* e) {
    printf("{%d -> %d, %d, %d}", e->v1, e->v2, e->weight, e->color);
}

int main()
{
  struct edge edges[] = {
    {0, 3, 3, 0},
    {1, 3, 7, 0},
    {2, 3, 4, 0},
    {4, 3, 5, 0},
    {1, 2, 4, 0},
    {4, 1, 1, 0},
    {2, 4, 9, 0},
    {2, 0, 2, 0}
  };
  int num_edges = 8;
  int vertices[5] = {0};
  int num_vertices = 5;
  int i;
  vertices[0] = 1;
  while(1) {
    i = 0;
    int other_v = 0;
    struct edge* min = NULL;
    for(; i < num_edges; ++i) {
      // Ignore any edges we already added
      if(edges[i].color == 2) continue;
      if(edges[i].color == 0 &&
         ( vertices[edges[i].v1] == 1 ||
           vertices[edges[i].v2] == 1 )
        )
      {
        printf("Coloring Edge ");
        print_edge(&edges[i]);
        printf("\n");
        edges[i].color = 1;
      }
      other_v = (vertices[edges[i].v1] == 1) ? edges[i].v2 : edges[i].v1;
      // If we're considering the edge and if the other vertex
      // has not been explored, consider for minimum.
      if(edges[i].color == 1 && vertices[other_v] == 0) 
      {
        if(!min || min->weight > edges[i].weight) min = &edges[i];
      }
    }
    if(min) {
      // Add the edge and go again on the vertices
      printf("Adding Edge ");
      print_edge(min);
      printf("\n");
      min->color = 2;
      vertices[min->v1] = 1;
      vertices[min->v2] = 1;
      if(--num_vertices == 0) break;
    }
    else break;
  }
  printf("Results: \n");

  for(i=0; i < num_edges; ++i) {
    if(edges[i].color == 2) {
      print_edge(&edges[i]);
      printf("\n");
    }
  }
  
  return 0;
}
