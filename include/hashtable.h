#include <types.h>
#include <slist.h>

#ifndef HASH_TABLE
#define HASH_TABLE 0

typedef struct
{
	slist **table;
	uint32 ht_size;
} htable;

typedef struct
{
	char *str;
	void *data;
} ht_data;

/* create hash table */
htable *create_htable(uint32 ht_size);

/* hash string */
uint32 hash_str(char *str, uint32 size);

/* hash insert / edit */
ht_data *hash_insert(htable *ht, char *str, slist_t type, void *data);

/* hash table search */
status_t hash_search(htable *ht, char *str, void **data);

/* hash delete element */
void hash_delete_element(htable *ht, char *str);

#endif
