/*
   header for singly linked list
 */

#include <types.h>

#ifndef S_LINK_LIST
#define S_LINK_LIST 0

typedef struct s_link_list
{
	void *data;
	slist_t type;
	struct s_link_list *next;
} slist;

/* create node */
slist *create_node(slist_t type, void *data);

/* insert first */
status_t insert_first(slist **head, slist *node);

/* insert last */
status_t insert_last(slist **head, slist *node);

/* delete first */
void delete_first(slist **head);

/* delete last */
void delete_last(slist **head);

#endif
