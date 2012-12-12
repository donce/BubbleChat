#TODO: depend on .h files
client: client.o chat.o display.o bubble.o world.o
	g++ -o client client.o chat.o display.o bubble.o world.o -lSDL
clean:
	rm -f chat *.o
