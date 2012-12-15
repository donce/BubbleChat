#TODO: depend on .h files
CXXFLAGS = -g
client: client.o chat.o display.o bubble.o world.o
	g++ $(CXXFLAGS) -o client client.o chat.o display.o bubble.o world.o -lSDL
clean:
	rm -f client *.o
