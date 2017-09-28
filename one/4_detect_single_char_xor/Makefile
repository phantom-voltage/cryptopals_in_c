CC=gcc
CFLAGS=-I../../header/

LIB_DIR=../../lib/

LIBS=$(LIB_DIR)/xor.o

LINKS=

main: main.o $(LIBS)
	$(CC) -o main main.o $(LIBS) $(CFLAGS) $(LINKS)


.PHONY: clean

clean:
	-rm main main.o $(LIBS)
