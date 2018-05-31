.PHONY:all

all:server client

server:server.c
	gcc -o $@ $^ -pthread

client:client.c
	gcc -o $@ $^ -pthread

.PHONY:clean

clean:
	rm -f server client

