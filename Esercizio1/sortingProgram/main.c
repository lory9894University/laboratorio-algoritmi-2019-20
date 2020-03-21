#include <stdio.h>
#include "sorting.h"
#include <stdlib.h>
#include <string.h>

typedef struct _Record *RecordLink;

typedef struct _Record {
  int id, field2;
  float field3;
  char *field1;
} Record;

typedef struct {
  RecordLink *recordArray;
  size_t size;
} RecordColletion;

/** this function copies from a string to the relatives fields of the struct**/
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
  RecordLink *recordArray;
  RecordColletion records;
  int line=0, size=2;
  char textLine[1024];

  if((fPtr=fopen(filename,"r"))==NULL){
    printf("file %s not found \n",filename);
    exit(1);
  }

  recordArray = malloc(sizeof(RecordLink) * 2);
  while(fgets(textLine,1024,fPtr)!= NULL) {
    if (line >= size) {
      size *= 2;
      recordArray = realloc(recordArray, sizeof(RecordLink) * size);
    }
    recordArray[line] = malloc(sizeof(Record));
    copy_from_line(textLine, recordArray[line]);
    line++;
  }
  recordArray = realloc(recordArray, sizeof(RecordLink) * line);
  records.recordArray = recordArray;
  records.size = line;

  return records;
}

static int int_comparer(Record *record1, Record *record2) {
  return record1->field2 - record2->field2;
}

static int float_comparer(Record *record1, Record *record2) {
  float res = record1->field3 - record2->field3;
  if (res > 0)
    return 1;
  else if (res == 0)
    return 0;
  else return -1;
}

static int string_comparer(Record *record1, Record *record2) {
  return strcmp(record1->field1, record2->field1);
}

int main(int argv, char **argc) {
  RecordColletion records;
  FILE *fptr = fopen("out.csv", "w");

  if (argv != 2) {
    printf("insert as the first argument the pathname of the csv file\n");
    exit(1);
  }
  records = csv_reading(argc[1]);
  /*for (int i = 0; i <records.size ; ++i) {
    printf("%d %s %d %f\n",records.recordArray[i]->id,records.recordArray[i]->field1,records.recordArray[i]->field2,records.recordArray[i]->field3);
  }*/
  printf("\n\n");
  quick_sort((void *)records.recordArray, records.size, (cmpFunction) int_comparer);
  for (int i = 0; i < records.size; ++i) {
    fprintf(fptr, "%d %s %d %f\n", records.recordArray[i]->id, records.recordArray[i]->field1,
            records.recordArray[i]->field2, records.recordArray[i]->field3);
  }
  return 0;
}
