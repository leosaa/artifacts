CFLAGS=-Wall -O3 -g
CC=gcc

all: server

#data:
#	dd if=/dev/urandom of=data.bin bs=1k count=1000

server:
	@echo "Compiling server.c"
	$(CC) $(CFLAGS) -o server server.c

clean:
	rm -f server client data.bin *~ client-sf
