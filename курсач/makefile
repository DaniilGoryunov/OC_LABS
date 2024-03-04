all: client server

client:
	g++ client.cpp -o client -pthread -std=c++20

server:
	g++ server.cpp -o server -std=c++20

clean:
	rm -rf client server
