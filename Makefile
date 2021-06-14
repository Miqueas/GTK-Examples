CFLAGS  = `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0`
CC      = gcc
Files   = $(wildcard *.c)
Names   = $(subst .c, ${empty}, ${Files})

%:
	@[[ -d Bin ]] || mkdir Bin
	@echo -e "\e[2m>\e[0m \e[1;34mBuilding \e[33m$@.c\e[0m"
	${CC} ${CFLAGS} $@.c -o Bin/$@ ${LDFLAGS}
	@echo

all: ${Names}
	@echo -e "\e[2m>\e[0m \e[1;32mDone\e[0m"

clean:
	rm -rf Bin/${Names}