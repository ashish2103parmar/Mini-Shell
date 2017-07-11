TARGET := ../lib/libmyshell.so
SRC := $(wildcard *.c)
Cflag := -I ../include
Lflag := -L ../lib -lslist

all: ${TARGET}

${TARGET} : ${SRC}
		gcc -fPIC -shared $^ ${Lflag} ${Cflag} -o $@

clean:
		rm ${TARGET}
