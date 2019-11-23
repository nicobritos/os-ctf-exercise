GCC=gcc
GCCFLAGS=-Wall -std=c99 -pedantic -D _XOPEN_SOURCE=500
OUTFILE=server
SOURCES=server.c challengesHandler.c clientConnection.c


all: server client

server:
	cd new_server; $(GCC) $(SOURCES) -o $(OUTFILE) $(GCCFLAGS)

client:
	cd client; $(GCC) client.c -o client $(GCCFLAGS)

clean:
	cd new_server; rm $(OUTFILE)
	cd client; rm client

.PHONY: server client clean