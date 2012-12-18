CXXFLAGS=-g
client: network.o mutex.o server.o clients.o
	g++ -o server mutex.o server.o network.o clients.o -lpthread
clean:
	rm -f client *.o
