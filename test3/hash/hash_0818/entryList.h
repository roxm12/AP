#ifndef __ENTRY_LIST_H__
#define __ENTRY_LIST_H__
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
typedef int HData;
  typedef struct hashEntry{
HData key;//ip :address -> key
 struct hashEntry *nxt;
}Entry;

void insertList(Entry **, HData);
int deleteList(Entry **, HData);
int searchList(Entry *,HData);
void printList(Entry *);



#endif
