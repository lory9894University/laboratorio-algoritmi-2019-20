#include <stdio.h>
#include "sorting.h"
#include <stdlib.h>
#include <string.h>

typedef struct{
  int id, field2;
  float field3;
  char * field1;
}Record;

typedef struct {
  Record * recordArray;
  size_t size;
}RecordColletion;

/* this function copies from a string to the relatives fields of the struct*/
void copy_from_line(char *line,Record *record){
  char *token;
  char tempField1[1024];

  token=strtok(line,",");
  record->id=atoi(token);
  token=strtok(NULL,",");
  strcpy(tempField1,token);
  token=strtok(NULL,",");
  record->field2=atoi(token);
  token=strtok(NULL,",");
  record->field3=atof(token);

  record->field1=malloc(sizeof(char)*strlen(tempField1));
  strcpy(record->field1,tempField1);
}

RecordColletion csv_reading(char * filename){
  FILE *fPtr;
  Record * recordArray;
  RecordColletion records;
  int line=0, size=2;
  char textLine[1024];

  if((fPtr=fopen(filename,"r"))==NULL){
    printf("file %s not found \n",filename);
    exit(1);
  }

  recordArray = malloc(sizeof(Record)*2);
  while(fgets(textLine,1024,fPtr)!= NULL){
    if (line >= size) {
      size *=2;
      recordArray = realloc(recordArray, sizeof(Record)*size);
    }
    copy_from_line(textLine,&recordArray[line]);
    line++;
  }
  recordArray = realloc(recordArray, sizeof(Record)*line);
  records.recordArray=recordArray;
  records.size=line;

  return records;
}

int main(int argv,char ** argc) {
  RecordColletion records;

  if (argv != 2){
    printf("insert as the first argument the pathname of the csv file\n");
    exit(1);
  }
  records = csv_reading(argc[1]);
  for (int i = 0; i <records.size ; ++i) {
    printf("%d %s %d %f",records.recordArray[i].id,records.recordArray[i].field1,records.recordArray[i].field2,records.recordArray[i].field3);
  }
  return 0;
}
