all: server client
server: 
	gcc -O -DLINUX server.c -o nweb
client:
	gcc -O -DLINUX client.c -o client

clean:
	rm nweb client
