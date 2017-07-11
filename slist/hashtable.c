#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <common.h>
#include <types.h>
#include <slist.h>
#include <hashtable.h>

/* create hash table */
htable *create_htable(uint32 ht_size)
{
	htable *ht = malloc(sizeof (ht));
	if (ht)
	{
		ht->ht_size = ht_size;
		ht->table = memset(malloc(ht_size * sizeof (slist *)), (int)NULL, ht_size * sizeof (slist *));
	}
	return ht;
}

/* hash string */
uint32 hash_str(char *str, uint32 size)
{
  uint32 hash = 0;
  while (*str)
  {
	hash = (hash + *str) % size;
	str++;
  }
  return hash;
}

/* hash insert / edit */
ht_data *hash_insert(htable *ht, char *str, slist_t type, void *data, int opt)
{
	if (!ht || !str)
		return (void *)-1;

	ht_data *hdata = malloc(sizeof (ht_data));

	if (!hdata)
		return (void *)-1;
	
	hdata->str = str;
	hdata->data = data;

	slist **head = &ht->table[hash_str(str, ht->ht_size)], *ptr;
	if (ptr = *head)
	{
		while (ptr)
		{
			if (!strcmp(((ht_data *)ptr->data)->str, str))
			{
				if (opt)
				{
					swap(ptr->data, hdata, ht_data *)
					return hdata;
				}
				else
					return (void *)-1;

			}
			if (!ptr->next)
				break;
			ptr = ptr->next;
		}
	}
	slist *node = create_node(type, (void *)hdata);

	if (ptr)
		ptr->next = node;
	else
		*head = node;
	return NULL;
}

/* hash table search */
status_t hash_search(htable *ht, char *str, void **data)
{
	if (!ht || !str || !data)
		return failure;

	slist *ptr = ht->table[hash_str(str, ht->ht_size)];

	while (ptr)
	{
		if (!strcmp(((ht_data *)ptr->data)->str, str))
		{
			*data = ((ht_data *)ptr->data)->data;
			return success;
		}
		ptr = ptr->next;
	}
	return failure;
}

/* hash delete element */
void hash_delete_element(htable *ht, char *str)
{
	if (!ht || !str)
		return;

	slist **head = &ht->table[hash_str(str, ht->ht_size)];
	slist *ptr = *head, *prev = NULL;
	while (ptr)
	{
		if (!strcmp(((ht_data *)ptr->data)->str, str))
		{
			free(ptr->data);
			if (prev)
				prev->next = ptr->next;
			else
				*head = ptr->next;
			free(ptr);
			return;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return;
}

/* to be done later*/
void hash_table_delete(htable *ht)
{
	free(ht);
}
