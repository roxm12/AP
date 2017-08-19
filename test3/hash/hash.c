#include <hash.h>


int hashfunc1(HData key);
int hashfunc2(int);
void initHashTable(FILE *f);
int search(HashTable *ht, HData key)
int insert(HashTable *ht, HData key){
	int idx=ht->hf1(key);
	if(ht->hash_entry[idx]==NULL){
	}else{
     idx=ht->hf2(idx);
     if(ht->hash_entry[idx]==NULL){
	 }else{
		  }

	 }
	}
	ht->entry_count++;

}
int delete(HashTable *ht, HData key);
