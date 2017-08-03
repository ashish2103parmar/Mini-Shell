SRCS  := $(wildcard *.c) $(wildcard shell/*.c) $(wildcard slist/*.c) 
TARGET := MYSHELL
#LFLAG := -L lib -lmyshell -lslist
CFLAG := -I include

all : ${TARGET} 

${TARGET}:${SRCS}
	gcc  $^ ${LFLAG} ${CFLAG} -o $@

clean:
		rm ${TARGET}
