#ifndef __HASH_H__
#define __HASH_H__
#include <stdio.h>
#include <stdllib.h>
#include <netinet/in.h>
#define MAX_ENTRY_NUM 1111
//DDT와 pair로 delete/ register /insert 등이 이루어 져야 한다.
//typedef struct in_adrr HData;
char *fname[MAX_CATEGORY_NUM-1]={"porn","ads","drug","gambling"};
typedef int HData;
typedef int (hFptr1*)(HData); 
typedef int (hFtpr2*)(int);
  typedef struct hashEntry{
HData key;//ip :address -> key
 struct hashEntry *nxt;
}EntryList;
typedef struct{

 EntryList *hash_entry[MAX_ENTRY_NUM];
 unsigned int entry_count;
 hFptr1 hf1;
 hFptr2 hf2;
}HashTable;

int hashfunc1(HData);
int hashfunc2(int);
void initHashTable(FILE * f);
int search(HastTable *, HData);
int insert(HastTable *, HData);
int delete(HashTable *, HData);




#endif
