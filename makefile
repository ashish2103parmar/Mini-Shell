SRCS  := $(wildcard *.c)
TARGET := $(SRCS:.c=.out)
LFLAG := -L ../lib 
CFLAG := -I ../include

all : ${TARGET} 

%.out:%.c
	gcc  $^ ${LFLAG} ${CFLAG} -o $@

clean:
		rm ${TARGET}
