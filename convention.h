#ifndef convention_H
#define convention_H
#include <stdbool.h>
// typedef int infotype;
#define MAX_STRING_LENGTH 100
typedef enum { INTEGER, STRING } DataType;
typedef union {
    int intValue;
    char strValue[MAX_STRING_LENGTH];
} infotype;
typedef struct tElmtList *address;
typedef struct tElmtList {
  infotype info;
  DataType type;
  address next;
} ElmtList;

#endif
