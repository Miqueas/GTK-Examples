CFLAGS  = $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS = $(shell pkg-config --libs gtk+-3.0)
CC      = gcc
Files   = $(wildcard *.c)
Names   = $(subst .c, ${empty}, ${Files})

%:
	${CC} ${CFLAGS} $@.c -o $@ ${LDFLAGS}

all: ${Names}
	@echo "Compiled all the examples"

clean:
	rm ${Names}