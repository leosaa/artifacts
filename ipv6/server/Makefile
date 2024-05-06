CFLAGS=-Wall -O3 -g
CC=gcc

all: server

server:
	@echo "Compiling server.c"
	$(CC) $(CFLAGS) -o server server.c

clean:
	rm -f server tx-file.img
