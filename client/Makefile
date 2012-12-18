#TODO: depend on .h files
client: network.o client.o chat.o display.o bubble.o world.o
	g++ -o client network.o client.o chat.o display.o bubble.o world.o -lSDL   -lpthread
clean:
	rm -f client *.o
