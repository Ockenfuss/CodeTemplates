


INCDIR=../includelib
srcfiles=$(wildcard *.c)
objfiles=$(srcfiles:.c=.o)

all: $(objfiles)

%.o: %.c Makefile
	gcc -c $< -g -iquote $(INCDIR)