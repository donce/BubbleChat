/*

written by: Rytis KarpuŠka
		rytis@elektromotus.lt
*/

#ifndef __NETWORK_H_
#define __NETWORK_H_

#include <stdint.h>

#define DEFAULT_PORT	1379
#define MSG_HEADER_SIZE	1

#include <iostream>


#include "bubble.h"

using namespace std;

enum {
	COMMAND_MOVE,
	COMMAND_CHAT,
	COMMAND_USER,
	COMMAND_DISCONNECT,
	COMMAND_CONNECT

};

typedef struct {
	int x;
	int y;
	int dirX;
	int dirY;

} movementCommand_t;


class Network {

private:
	int socketfd;
	Bubble *me;

	void parseMovementCommand(uint8_t *buff, int size);
	void parseChatCommand(uint8_t *buff, int size);
	void parseUserCommand(uint8_t *buff, int size);
	void parseUserDelCommand(uint8_t *buff, int size);



public:
	~Network();
	Network();


	int initConnection(Bubble *b, char *addr, int port = DEFAULT_PORT);
	void waitForData();
	int sendData(uint8_t *data, int length);
	bool sendPos(movementCommand_t move);
	bool sendMessage(uint8_t *text);
	bool sendDisconnect();
	bool sendConnect();

}; 



#endif
