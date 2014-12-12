SOURCES = server\main.c
CLIENT_SOURCES = client\main.c
HEADERS = common\initsock.h

all:
	gcc $(SOURCES) -lws2_32 -o server
	gcc $(CLIENT_SOURCES) -lws2_32 -o client

clean:
	rm server.exe client.exe
