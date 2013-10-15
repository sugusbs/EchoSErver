OBJECTS=server client
SRCS=tcpserver.c tcpclient.c

all: $(OBJECTS)

server: tcplib.h tcpserver.c
	gcc -o server tcpserver.c

client: tcplib.h tcpclient.c
	gcc -o client tcpclient.c
clean:
	rm -rf $(OBJECTS)
