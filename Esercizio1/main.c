#include <stdio.h>
#include "sorting.h"
#include <stdlib.h>

typedef struct{
  int id, field2;
  float field3;
  char * field1;
}Record;

Record * csv_reading(char * filename){
  FILE *fPtr;
  Record * recordArray;
  int line=0, size=0;

  if((fPtr=fopen(filename,"r"))==NULL){
    printf("file %s not found \n",filename);
    exit(1);
  }

  recordArray = malloc(sizeof(Record)*2);
  do{
    line++;
    if (line >= size) {
      size *=2;
      recordArray = realloc(recordArray, sizeof(Record)*size);
    }
  }
  while (fscanf(fPtr,"%d,%s,%d,%f",&recordArray[line].id,recordArray[line].field1,&recordArray[line].field2,&recordArray[line].field3));
  line--;
  recordArray = realloc(recordArray, sizeof(Record)*line);

  return recordArray;
}

int main(int argv,char ** argc) {
  Record* recordArray;

  if (argv != 2){
    printf("insert as the first argument the pathname of the csv file\n");
    exit(1);
  }
  recordArray = csv_reading(argc[1]);
  printf("Hello, World!\n");
  return 0;
}
