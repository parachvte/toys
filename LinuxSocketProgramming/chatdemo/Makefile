

GCC=g++ -std=c++11

all: server client

server:
	$(GCC) chat_server.cpp sock_util.cpp -o chat_server

client:
	$(GCC) chat_client.cpp sock_util.cpp -o chat_client

clean:
	rm chat_server chat_client
