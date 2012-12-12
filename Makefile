#TODO: depend on .h files
chat: chat.cpp display.o bubble.o world.o
	g++ chat.cpp -o chat display.o bubble.o world.o -lSDL
clean:
	rm -f chat *.o
