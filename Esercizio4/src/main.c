#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Change *link;
typedef struct _MemNode * nextNode;
typedef struct _Edge *nextEdge;

/**a single change, can be used as a list of changes**/
typedef struct _Change {
  int x, y;
  int weight;
  link next;
} Change;

/**the base component used to create the adjacences list**/
typedef struct _Edge{
  int weight, to;
  nextEdge next;
} edge;

/**this struct has a double use: it can be used as the base element to create the
 *adjacences matrix or (more important) can be used to store "path" from 2 nodes.
 *It's not used in my program because i can't make memoization working*/
typedef struct _MemNode{
  int weight;
  int nextId;
  nextNode memoLink;
}memNode;

/**generic wrapper for the graph**/
typedef struct {
  nextNode **adjMatrix;
  nextEdge * adjList;
  int nodes;
} Graph;

/**creation of a new node**/
link new_node(link next) {
  link x = malloc(sizeof(struct _Change));
  x->next = next;
  return x;
}

/**creation of a new edge**/
nextEdge new_edge(nextEdge next){
  nextEdge x = malloc(sizeof(struct _Edge));
  x->next=next;
  return x;
}

/**reading the file having "filename" path and saving graph information in the adjList and in the memoization matrix**/
link copy_file(char *filename, Graph *graph, int *changeNum) {
  FILE *fPtr;
  link head, node;
  int linesAfter;
  int from, to;
  int x, y, weight;

  if ((fPtr = fopen(filename, "r")) == NULL) {
    printf("file %s not found \n", filename);
    exit(1);
  }

  fscanf(fPtr, "%d\n", &linesAfter);
  graph->nodes = linesAfter;
  graph->adjMatrix = malloc(sizeof(nextNode*) * 100001);
  graph->adjList = malloc(sizeof(nextEdge)*100001); //dirty bodge, but I prefere wasting 32 bit than an hour debugging
  for (int i = 0; i < 100001 ; ++i) {
    graph->adjMatrix[i] = malloc(sizeof(nextNode) * 100001-i); //i only need the lower half of the matrix
  }
  for (int i = 0; i < linesAfter-1; ++i) {
    fscanf(fPtr, "%d %d %d\n", &x, &y, &weight);
    graph->adjList[x]=new_edge(graph->adjList[x]);
    graph->adjList[x]->weight=weight;
    graph->adjList[x]->to=y;
    graph->adjList[y]=new_edge(graph->adjList[y]);
    graph->adjList[y]->weight=weight;
    graph->adjList[y]->to=x;

    if (x>y){
      from=x;
      to=y;
    } else{
      from=y;
      to=x;
    }
    graph->adjMatrix[from][to]= malloc(sizeof(nextNode));
    graph->adjMatrix[from][to] ->weight= weight;
    graph->adjMatrix[from][to] ->nextId= to;
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

/**
 * finds a path between 2 nodes, can be used recursively or with the help of the memoization matrix (stored in the struct _Graph)
 * right now i tried to use the dynamic programming paradigm but my solution doesen't seem correct, so im' using simple recursion
 */
int pathFind(Graph graph,int from, int to,int noLoop, memNode * path){
  nextEdge head= graph.adjList[from];
  nextNode new;
  int found=0;
  //base case
  if (from==to){
    return 1;
  }

  while (head != NULL){
    if (head->to == noLoop){
      head=head->next;
      continue;
    }
    found=pathFind(graph, head->to, to, from, path);
    if (found){
      new=malloc(sizeof(memNode));
      new->memoLink=path->memoLink;
      new->nextId = head->to;
      new->weight = head->weight;
      path->memoLink = new;
      return 1;
    }
    head = head->next;
  }

  return 0;
}

/** analize the path between 2 nodes, returns yes if the new edge makes this path lighter, no otherwise*/
char pathAnalize(memNode *path, int weight) {
  memNode *next = path->memoLink;
  while (next != NULL) {
    if (next->weight > weight)
      return 'y';
    next = next->memoLink;
  }
  return 'n';
}

/**given a new edge this function finds the path between the two vertexs of the edge.
 * then analyze this path and return yes if the new edge makes the graph lighter*/
char is_graph_lower(Graph graph, Change singleChange) {
  int from, to;
  memNode * path = malloc(sizeof(memNode));

  if (singleChange.x>singleChange.y){
    from=singleChange.x;
    to=singleChange.y;
  } else{
    from=singleChange.y;
    to=singleChange.x;
  }

  if (graph.adjMatrix[from][to] != NULL && graph.adjMatrix[from][to]->weight > singleChange.weight)
    return 'y';

  pathFind(graph,from,to,-1,path);
  return pathAnalize(path,singleChange.weight);
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
