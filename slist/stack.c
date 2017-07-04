/*
 * stack lib
 */

#include <stdio.h>
#include <stdlib.h>
#include <types.h>
#include <slist.h>
#include <stack.h>

/* push to stack */
status_t push(stack *sptr, slist *node)
{
	return insert_first(sptr, node);
}

/* pop from stack */
status_t pop(stack *sptr, slist **node)
{
	if (!*sptr)
	{
		error_msg("stack is empty");
		return failure;
	}

	*node = *sptr;
	(*node)->next = NULL;

	delete_first(sptr);
	return success;
}

