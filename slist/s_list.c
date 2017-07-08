/*
 * singly linked list lib
 */
#include <stdio.h>
#include <stdlib.h>
#include <types.h>
#include <slist.h>


/* create node */
slist *create_node(slist_t type, void *data)
{
	slist *node = malloc(sizeof (slist));
	if (node)
	{
		node->type = type;
		node->data = data;
		node->next = NULL;
	}
	else 
		error_msg("Allocation failure, node not created");
	return node;
}

/* insert first */
status_t insert_first(slist **head, slist *node)
{
	if (!node)
	{
		error_msg("Insert failure, node is NULL");
		return failure;
	}

	node->next = *head;
	*head = node;
	return success;
}


/* insert last */
status_t insert_last(slist **head, slist *node)
{
	if (!node)
	{
		error_msg("Insert failure, node is NULL");
		return failure;
	}

	if (*head)
	{
		slist *ptr = *head;
		while (ptr  && ptr->next)
			ptr = ptr->next;

		ptr->next = node;
	}
	else
		*head = node;

	return success;
}

/* delete first */
void delete_first(slist **head)
{
	if (*head)
	{
		slist *ptr = *head;
		*head = ptr->next;

		free(ptr);
	}
}


/* delete last */
void delete_last(slist **head)
{	
	if (*head)
	{
		slist *ptr = *head;
		if (!ptr->next)
		{
			free(ptr);
			*head = NULL;
		}
		else
		{
			while (ptr && ptr->next && ptr->next->next)
				ptr = ptr->next;

			free(ptr->next);
			ptr->next = NULL;
		}
	}
}


