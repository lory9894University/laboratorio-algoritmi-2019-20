#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Edge *nextEdge;
typedef struct _Change *link;

typedef struct {
  nextEdge * vertexes; //dirty bodge, but I prefere wasting 16 bit than an hour debugging
  int nodes;
} Graph;

typedef struct _Edge{
  int weight, to;
  nextEdge next;
} edge;

/**a single change, can be used as a list of changes**/
typedef struct _Change {
  int x, y;
  int weight;
  link next;
} Change;

/**creation of a new edge**/
nextEdge new_edge(nextEdge next){
  nextEdge x = malloc(sizeof(struct _Edge));
  x->next=next;
  return x;
}
/**creation of a new node in the changes list**/
link new_node(link next) {
  link x = malloc(sizeof(struct _Change));
  x->next = next;
  return x;
}

/**reading of the file having "filename" path**/
link copy_file(char *filename, Graph *graph, int *changeNum) {
  FILE *fPtr;
  link head, node;
  int linesAfter;
  int x, y, weight;

  if ((fPtr = fopen(filename, "r")) == NULL) {
    printf("file %s not found \n", filename);
    exit(1);
  }

  fscanf(fPtr, "%d\n", &linesAfter);
  graph->nodes = linesAfter;
  graph->vertexes = malloc(sizeof(nextEdge)*100001);
  for (int i = 1; i < linesAfter; ++i) {
    fscanf(fPtr, "%d %d %d\n", &x, &y, &weight);
    graph->vertexes[x]=new_edge(graph->vertexes[x]);
    graph->vertexes[x]->weight=weight;
    graph->vertexes[x]->to=y;
    graph->vertexes[y]=new_edge(graph->vertexes[y]);
    graph->vertexes[y]->weight=weight;
    graph->vertexes[y]->to=x;

  }


  fscanf(fPtr, "%d\n", &linesAfter);
  *changeNum = linesAfter;
  head = malloc(sizeof(link *));
  node = head;
  for (int i = 0; i < linesAfter; ++i) {
    if (i != 0) {
      node->next = new_node(NULL);
      node = node->next;
    }
    fscanf(fPtr, "%d %d %d\n", &x, &y, &weight);
    node->x = x;
    node->y = y;
    node->weight = weight;
  }
  return head;
}

void write_out(char *filename, char *yesArray) {
  FILE *fPtr;
  int i = 0;

  if ((fPtr = fopen(filename, "w")) == NULL) {
    printf("error creating the file %s, check permission\n", filename);
    exit(1);
  }

  while (yesArray[i] != '\0') {
    if (yesArray[i] == 'y')
      fprintf(fPtr, "YES\n");
    else
      fprintf(fPtr, "NO\n");

    i++;
  }
}

char is_graph_lower(Graph graph, Change singleChange) {
  return 'n';
}

int main(int argv, char **argc) {
  Graph graph;
  link changesHead;
  int changeNum;
  char *yesArray;

  if (argv != 3) {
    printf("insert as the first argument the pathname of the input file\n"
           "as the second argument the pathname of the output file\n");
    exit(1);
  }

  changesHead = copy_file(argc[1], &graph, &changeNum);
  yesArray = malloc(sizeof(char) * changeNum);
  for (int i = 0; i < changeNum; ++i) {
    yesArray[i] = is_graph_lower(graph, *changesHead);
    changesHead = changesHead->next;
  }
  write_out(argc[2],yesArray);
  free(yesArray);

}
