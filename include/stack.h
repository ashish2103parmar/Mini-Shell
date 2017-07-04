#include <types.h>
#include <slist.h>

#ifndef STACK
#define STACK 0

typedef slist* stack;

/* push to stack */
status_t push(stack *sptr, slist *node)

/* pop from stack */
status_t pop(stack *sptr, slist **node)

#endif
