all: server 
server: 
	gcc -O -DLINUX server.c -o nweb
