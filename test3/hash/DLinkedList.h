#ifndef __D_LINKED_LIST_H__
#define __D_LINKED_LIST_H__
#include <netinet/in.h>

//typedef struct in_addr LData;
typedef int LData;

typedef struct _node{
  struct _node * nxt;
  LData key;
}Node;
typedef struct _linkedList{
Node *head;
Node *cur;
Node *before;
int numOfData;
}List;

void listInit(List *list);
void listInsert(List *list,LData data);
int listFirst(List *list, LData *data);
int listNext(List *list, LData *data);
LData listRemove(List *list);
int listCount(List *list);




#endif
