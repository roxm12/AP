#ifndef __FILTER_H__
#define __FILTER_H__
#include "../ddt/ddt.h"
#define MAX_ENTRY_NUM 1111
//DDT와 pair로 delete/ register /insert 등이 이루어 져야 한다.
char *fname[MAX_CATEGORY_NUM-1]={"porn","ads","drug","gambling"};
typedef int (*hashFptr1)(struct in_addr);

typedef int (*hashFptr2)(int);

typedef struct{
 struct in_addr ipAddr;

}Entry;
typedef struct{

 Enty hash_entry[MAX_ENTRY_NUM];
 unsigned int entry_num;
}HashTable;

typedef struct categoryFilteringPool{

struct CategoryFilteringPool * next_host;
HashTable ht;
char *macAddr;
}CFP;

typedef struct categoryFilteringPoolList{

CFP block_List[MAX_CATEGORY_NUM];
hashFptr1 fptr1;
hashFptr2 fptr2;
}CFPL;

void initCFPL(CFPL * bipList);



#endif
