chat: chat.cpp display.o bubble.o
	g++ chat.cpp -o chat display.o bubble.o -lSDL
clean:
	rm -f chat *.o
