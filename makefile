SRCS  := $(wildcard *.c)
TARGET := $(SRCS:.c=.out)
LFLAG := -L ../Lib -lrbtree
CFLAG := -I ../Include

all : ${TARGET} 

%.out:%.c
	gcc  $^ ${LFLAG} ${CFLAG} -o $@

clean:
		rm ${TARGET}
