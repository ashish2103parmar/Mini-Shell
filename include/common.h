#ifndef COMMON
#define COMMON 1
	
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <fcntl.h>

#define swap(X, Y, type) {	\
	type temp;				\
	temp = X;  				\
	X = Y;					\
	Y = temp;				\
}

#endif
