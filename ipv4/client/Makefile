CFLAGS=-Wall -O3 -g
CC=gcc

all: clientw client-sf

clientw:
	@echo "Compiling clientw.c"
	$(CC) $(CFLAGS) -o clientw clientw.c

client-sf:
	@echo "Compiling client-sf.c"
	$(CC) $(CFLAGS) -o client-sf client-sf.c
clean:
	rm -f clientw file-* client-sf
