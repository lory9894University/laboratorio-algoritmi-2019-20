#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int **adjMatrix;
  int nodes;
  //todo: matrice di adiacenze o lista? matrice perchè necessita di meno tempo a discapito della memoria
} Graph;

typedef struct _Change *link;
/**a single change, can be used as a list of changes**/
typedef struct _Change {
  int x, y;
  int weight;
  link next;
} Change;

/**creation of a new node**/
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
  graph->adjMatrix = malloc(sizeof(int*) * 100000);
  for (int i = 0; i < 100000 ; ++i) {
    graph->adjMatrix[i] = malloc(sizeof(int) * 100000);
    graph->adjMatrix[i] = calloc(100000, sizeof(int));
    /*vorrei lasciare qui un commento, in maniera poco professionale, a ricordo del fatto
     * che ho perso 3 intere ore per capire come inizializzare a 0 in maniera efficiente questa matrice.
     * in questa mia ricerca sono pure incappato in un bug che mandava completamente in crash il pc, vai a capire.
     * salvo poi ricordarmi l'esistenza della funzione calloc*/
  }
  for (int i = 0; i < linesAfter-1; ++i) {
    fscanf(fPtr, "%d %d %d\n", &x, &y, &weight);
    graph->adjMatrix[x][y] = weight;
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

char is_graph_lower(Graph *graph, Change singleChange) {
  if (graph->adjMatrix[singleChange.x][singleChange.y] > singleChange.weight)
    return 'y';

  //todo:implementare dijkstra o bellman ford (anche solo una deep-first search), cerca di farlo dopo che lo farai a lezione
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
    yesArray[i] = is_graph_lower(&graph, *changesHead);
    changesHead = changesHead->next;
  }

  free(yesArray);

}
