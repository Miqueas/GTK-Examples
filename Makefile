GTK3_INC = `pkg-config --cflags gtk+-3.0`
GTK3_LIB  = `pkg-config --libs gtk+-3.0`
CC         = gcc
Files      = $(wildcard *.c)
Names      = $(subst .c, ${empty}, ${Files})

%:
	${CC} ${GTK3_INC} $@.c -o $@ ${GTK3_LIB}

all: ${Names}
	@echo "Compiled all the examples"

clean:
	rm ${Names}