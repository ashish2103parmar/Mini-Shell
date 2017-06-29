/*
   header for singly linked list
 */

#include <types.h>

#ifndef S_LINK_LIST
#define S_LINK_LIST 0

typedef struct s_link_list
{
	void *ptr;
	slist_t type;
	struct s_link_list *next;
} slist;

#endif
