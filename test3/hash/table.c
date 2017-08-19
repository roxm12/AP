#include "table.h"
#include <stdio.h>
#include <stdlib.h>



void tblInit(Table *pt, hashFptr1 f){
	int i;
	for(i=0;i<MAX_TBL;i++){

		listInit(&(pt->tbl[i]));
		pt->hf=f;
	}
}
void tblInsert(Table *pt, LData key){
  int hv=pt->hf(key);
  if(tblSearch(pt,key)){//duplicate key value
	  perror("duplicate hash key");
	  return;
  }else{
	  listInsert((&pt->tbl[hv]),key);
  }

}
void tblDelete(Table *pt, LData key);
void tblDelete(Table *pt, LData key);
int tblSearch(Table *pt, LData key){

  int hv=pt->hf(key);
  LData hashData;
  if(listFirst(&(pt->tbl[hv]),&hashData)){
	  if(hashData == key)return 1;
  }else{
	  while(listNext((&pt->tbl[hv]),&hashData)){
		  if(hashData == key)return 1;
	  }
  }
  return 0;
}

#endif
