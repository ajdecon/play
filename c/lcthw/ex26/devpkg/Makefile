PREFIX?=/usr/local
CFLAGS=-g -Wall -I/usr/include/apr-1 
LDFLAGS=-L/usr/lib64 -lapr-1 -lpthread -laprutil-1

all: devpkg

devpkg: bstrlib.o db.o shell.o commands.o

install: all
	install -d $(DESTDIR)/$(PREFIX)/bin/
	install devpkg $(DESTDIR)/$(PREFIX)/bin/

clean:
	rm -f *.o
	rm -f devpkg
	rm -rf *.dSYM
