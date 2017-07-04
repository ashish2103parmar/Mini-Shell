/*
 * queue lib
 */

#include <stdio.h>
#include <stdlib.h>
#include <types.h>
#include <slist.h>
#include <queue.h>

/* en queue */
status_t en_queue(queue *qptr, slist *node)
{
	return insert_last(qptr, node);
}

/* de queue */
status_t de_queue(queue *qptr, slist **node)
{
	if (!qptr)
	{
		error_msg("queue is empty");
		return failure;
	}

	*node = qptr;
	(*node)->next = NULL;

	delete_first(qptr);
	return success;
}
