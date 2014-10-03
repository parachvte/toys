

GCC=gcc

all: server client

server:
	$(GCC) chat_server.c sock_util.c -o chat_server

client:
	$(GCC) chat_client.c sock_util.c -o chat_client

clean:
	rm chat_server chat_client
