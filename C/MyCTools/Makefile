



CC=gcc
CFLAGS=-lm
LFLAGS=-g



PArray_test:PArray_test.o PArray.o
	$(CC) -o $@ $^ $(LFLAGS)
LinArray_test:LinArray_test.o LinArray.o
	$(CC) -o $@ $^ $(LFLAGS)



%.o: %.c %.h
	$(CC) -c $< $(CFLAGS)