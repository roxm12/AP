#include "entryList.h"

int main(){

Entry *a;
insertList(&a,2);
insertList(&a,3);
insertList(&a,4);
//insertList(&a,3);
//insertList(&a,4);
//insertList(&a,5);
//insertList(&a,6);
//insertList(&a,7);
//printList(a);
//if(searchList(&a,3))printf("3 is found\n");
//printList(a);
//deleteList(a,3);
deleteList(&a,2);
//deleteList(a,1);
//if(!deleteList(a,1))printf("1 is not found\n");
//printList(&a);
deleteList(&a,1);
deleteList(&a,3);
printList(a);
//if(!searchList(&a,3))printf("3 is not found\n");
deleteList(&a,4);
printList(a);
return 0;
}
