



CC=gcc
CFLAGS=-lm
LFLAGS=-g



MyCTools_test:MyCTools_test.o MyCTools.o
	$(CC) -o $@ $^ $(LFLAGS)



%.o: %.c %.h
	$(CC) -c $< $(CFLAGS)