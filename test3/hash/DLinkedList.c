#include "DLinkedList.h"
#include <stdio.h>
#include <stdlib.h>

void listInit(List *list){

	list->head=(Node*)malloc(sizeof(Node));
	list->head->nxt=NULL;
	list->numOfData=0;
}
void listInsert(List *list,LData data){

	Node * newNode=(Node*)malloc(sizeof(Node));
	newNode->key=data;
    newNode->nxt=list->head->nxt;
	list->head->nxt=newNode;
    (list->numOfData)++;
}
int listFirst(List *list,LData *data){

	if(list->head->nxt==NULL)
		return 0;
	list->before=list->head;
	list->cur=list->head->nxt;
	*data=list->cur->key;
	return 1;

}
int listNext(List *list,LData *data){
    if(list->cur->nxt==NULL)
		return 0;
	list->before=list->cur;
	list->cur=list->cur->nxt;
	*data=list->cur->key;
	return 1;

}
LData listRemove(List *list){
 Node *removePos=list->cur;
 LData removeData=removePos->key;
 list->before->nxt=list->cur->nxt;
 free(removePos);
 (list->numOfData)--;
 return removeData;

}
int listCount(List *list){
return list->numOfData;
}
