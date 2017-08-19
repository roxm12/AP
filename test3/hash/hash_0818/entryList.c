#include "entryList.h"


void  insertList(Entry **list, HData key){
	Entry *insert=(Entry*)malloc(sizeof(Entry));
	insert->key=key;
	insert->nxt=NULL;
	if(*list==NULL){
		*list=insert;
	}
	else{
		insert->nxt=(*list)->nxt;
		(*list)->nxt=insert;
	}
}
int deleteList(Entry **list, HData key){
	Entry **temp,**delete;
	if(*list==NULL){//Null node
		return 0;
	}else if((*list)->nxt == NULL){//1st node
         if((*list)->key == key){
			 free(*list);
			 *list=NULL;
			 return 1;
		 }
	}
	else{//gt node2
		temp=delete=list;//temp is precedance 
		while( *delete != NULL){
			if((*delete)->key == key){
			    (*temp)->nxt=(*temp)->nxt->nxt;	
				free(*delete);
				*delete = NULL;
				return 1;
				}
			
		*temp= *delete;
		*delete= (*delete)->nxt;
		}
	}
	return 0;
}
int searchList(Entry *list,HData key){
	Entry* temp;
	if(list==NULL)return 0;
	else{
		temp= list;
		while(temp != NULL){
			if(temp->key == key)return 1;
			temp=temp->nxt;
		}
	}
	return 0;
}
void printList(Entry *list){
	Entry* temp;
	if(list==NULL)return;
	else {
		temp= list;
		while(temp != NULL){
			printf("%10d",temp->key);
			temp=temp->nxt;
		}
		printf("\n");
	}
}
