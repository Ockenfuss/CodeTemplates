


INCDIR=../includelib
srcfiles=$(wildcard *.c)
objfiles=$(srcfiles:.c=.o)

all: $(objfiles)

%.o: %.c
	gcc -c $< -iquote $(INCDIR)