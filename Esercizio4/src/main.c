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

typedef struct _Edge{
  int weight, to;
  nextEdge next;
} edge;

typedef struct _MemNode{
  int weight;
  int nextId;
  nextNode memoLink;
}memNode;

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

/**reading the file having "filename" path**/
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

void pathFind(Graph graph,int from, int to, memNode * path){
  memNode * new;
  nextEdge head;
  if (graph.adjMatrix[from][to]==NULL){
    head=graph.adjList[from];
    while (head!=NULL){
      pathFind(graph,head->to,to,path);
      head=head->next;
    }
    //save in MemoizationMatrix
    new = malloc(sizeof(memNode));
    graph.adjMatrix[from][to]=path;
    //save in the list
    new ->memoLink=path->memoLink;
    path->memoLink=new;
  } else{
    //prelevalo dalla matrice dinamica e salvalo nella lista
    new=graph.adjMatrix[from][to];
    while (new->memoLink!=NULL)
      new=new->memoLink;
    new ->memoLink=path->memoLink;
    path->memoLink=graph.adjMatrix[from][to];
  }

 return;
}
char pathAnalize(memNode * path,int weight){
  memNode * next = path;
  while (next != NULL){
    if (next->weight< weight)
      return 'y';
    next = next->memoLink;
  }
  return 'n';
}

char is_graph_lower(Graph graph, Change singleChange) {
  int from, to;
  memNode * path = malloc(sizeof(memNode));
  memNode * rm = path;

  if (singleChange.x>singleChange.y){
    from=singleChange.x;
    to=singleChange.y;
  } else{
    from=singleChange.y;
    to=singleChange.x;
  }

  if (graph.adjMatrix[from][to] != NULL && graph.adjMatrix[from][to]->weight > singleChange.weight)
    return 'y';

  pathFind(graph,from,to,path);
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
