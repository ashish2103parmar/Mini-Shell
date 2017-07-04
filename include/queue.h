#include <types.h>

#ifndef QUEUE
#define QUEUE 0

typedef slist* queue;

/* en queue */
status_t en_queue(queue *qptr, slist *node)

/* de queue */
status_t de_queue(queue *qptr, slist **node)

#endif 
