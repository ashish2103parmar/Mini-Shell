/*
   header for different types
 */
#include <common.h>

#ifndef MS_TYPES
#define MS_TYPES 0

typedef enum
{
	failure = 0,
	success
} status_t;

typedef enum
{
	T_INT,
	T_STR
} slist_t;

typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

#endif
