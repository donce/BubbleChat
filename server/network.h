/*


	Server for bubble chat project
	Author: Rytis KarpuŠka
		rytis@elektromotus.lt

*/

#ifndef __NETWORK_H_
#define __NETWORK_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "moveType.h"
#include "clients.h"
#include "mutex.h"
#include <vector>

#define MESSAGE_HEADER_SIZE		2
#define DEFAULT_PORT  			1379
#define NUM_OF_THREADS			2
#define DEFAULT_MAX_CLIENTS		15
#define MAX_SUPPORTED_CLIENTS		1000

using namespace std;

enum {
	COMMAND_MOVE,
	COMMAND_CHAT,
	COMMAND_USER,
	COMMAND_DISCONNECT,
	COMMAND_CONNECT
};

class Network {

private:
	Mutex clientStackMutex;
	int maxClients;
	vector<int> clientFD;	
	int socketfd;
	sockaddr_in sAddr;
	socklen_t sLen;
	clients cls;

	void sendData(int idx, uint8_t *data, int size);
	void parseMovementCommand(int idx, int sockFD, uint8_t *buff, int size);
	void parseChatCommand(int idx, int sockFD, uint8_t *buff, int size);
	void parseDisconnectCommand(int idx, int sockFD, uint8_t *buff, int size);
	void parseConnectCommand(int idx, int sockFD, uint8_t *buff, int size);




public:
	Network();
	~Network();

 	bool init(int port = DEFAULT_PORT, int maxClients = DEFAULT_MAX_CLIENTS);
	void *waitForConnection();
	void *processTransmittedData();
	void sendPos(int idx, int moveIdx, movementCommand_t move);
	void sendMsg(int idx, int id, char *msg);
	void sendUser(int idx, client c);
	void sendUserDel(int idx, int id);
	int numOfClients();


};



#endif
