/*

written by: Rytis KarpuŠka
		rytis@elektromotus.lt
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <pthread.h>
#include <stdint.h>
#include <time.h>

#include <sys/socket.h>
#include <netdb.h>

#include "chat.h"
#include "network.h"



using namespace std;

Network::Network()
{
	//mark our socket as invalid before connecting
	socketfd = -1;

	return;
}

Network::~Network()
{
	sendDisconnect();

	return;
}

int Network::sendData(uint8_t *data, int length)
{
	timespec time = {0, 10};
	nanosleep(&time, NULL);

	return send(socketfd, data, length, MSG_EOR);
}


void Network::parseMovementCommand(uint8_t *buff, int size)
{
	if(size != 2 + sizeof(movementCommand_t))
		return;

	movementCommand_t move;

	int id = buff[1];
	memcpy(&move, &buff[2], sizeof(movementCommand_t));
	
	Point pos;
	pos.x = move.x;
	pos.y = move.y;
	Point dir;
	dir.x = move.dirX;
	dir.y = move.dirY;

	//find which bubble is this
	for(int i = 0; i < chatObject->bubbleCnt(); i++)
		if(chatObject->bubbleAt(i)->getID() == id){
			chatObject->bubbleAt(i)->setPos(pos);
			chatObject->bubbleAt(i)->setDir(dir);
		}

	return;
}

void Network::parseChatCommand(uint8_t *buff, int size)
{
	if(size <= 2)
		return;

	int id = buff[1];
	char *text = (char *)&buff[2];

	int i;
	for(i = 0; i < chatObject->bubbleCnt(); i++)
		if(chatObject->bubbleAt(i)->getID() == id)
			break;

	printf("%s: %s\n", chatObject->bubbleAt(i)->getName().c_str(), text);


	return;
}

void Network::parseUserCommand(uint8_t *buff, int size)
{
	printf("user command received\n");

	movementCommand_t move;
	memcpy(&move, &buff[1], sizeof(move));

	int id;
	memcpy(&id, &buff[1 + sizeof(move)], sizeof(id));

	//name gathering
	char *name;
	name = (char *)&buff[1 + sizeof(move) + sizeof(id)];

	Bubble *b = new Bubble();

	Point pos;
	pos.x = move.x;
	pos.y = move.y;
	Point dir;
	dir.x = move.dirX;
	dir.y = move.dirY;
	std::string strName(name);

	b->setPos(pos);
	b->setDir(dir);
	b->setName(strName);
	b->setID(id);

	chatObject->addBubble(*b);	

	return;
}


void Network::parseUserDelCommand(uint8_t *buff, int size)
{
	printf("User del command received\n");

	int id;
	memcpy(&id, &buff[1], sizeof(id));

	chatObject->remBubble(id);

	return;
}


void Network::waitForData()
{
	uint8_t buff[1024];
	int size;

	while(true){
		timespec time = {0, 1000};
		nanosleep(&time, NULL); //introduce guard time
	
		memset(buff, 0, sizeof(buff));
	
		if((size = recv(socketfd, buff, sizeof(buff), 0)) <= 3)
			continue;

		switch(buff[0]){
		case COMMAND_MOVE:
			parseMovementCommand(buff, size);
			break;

		case COMMAND_CHAT:
			parseChatCommand(buff, size);
			break;

		case COMMAND_USER:
			parseUserCommand(buff, size);
			break;
	
		case COMMAND_DISCONNECT:
			parseUserDelCommand(buff, size);
			break;
		}	

	}

	return;
}

void *waitForDataWrapper(void *args)
{
	((Network *)args)->waitForData();

	return NULL;
}

int Network::initConnection(Bubble *b, char *addr, int port)
{
	//save me
	me = b;

	//create socket
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd < 0){
		fprintf(stderr, "Error creating socket\n");
		return false;
	}

	//extract data from arguments
	if(addr == NULL)
		return false;	

	struct hostent *host = gethostbyname(addr);
	if(host == NULL){
		fprintf(stderr, "Error no such host\n");
		return false;
	}

	//fill up socket address
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	memcpy(&serv_addr.sin_addr.s_addr, host->h_addr, host->h_length);
	serv_addr.sin_port = htons(port);

	//try to connect to server
	if(connect(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		fprintf(stderr, "Error could not connect to server\n");
		fprintf(stderr, "%s\n", strerror(errno));
		return false;
	}


	pthread_t myThreadHandle;

	//create thread for reading data
	pthread_create(&myThreadHandle, NULL, waitForDataWrapper, this);

	sendConnect();
	
 	return true;
}

bool Network::sendPos(movementCommand_t move)
{
	uint8_t buff[MSG_HEADER_SIZE + sizeof(movementCommand_t)];

	buff[0] = COMMAND_MOVE;
	memcpy(&buff[1], &move, sizeof(move));

	sendData(buff, sizeof(buff));

	return true;
}

bool Network::sendMessage(uint8_t *text)
{
	uint8_t buff[MSG_HEADER_SIZE + strlen((char *)text)];

	buff[0] = COMMAND_CHAT;
	memcpy(&buff[1], text, strlen((char *)text));

	sendData(buff, sizeof(buff));	

	return true;
}

bool Network::sendDisconnect()
{
	uint8_t buff[2];

	buff[0] = COMMAND_DISCONNECT;
	buff[1] = 5;//dummy byte (packet must be bigger than one byte)

	sendData(buff, sizeof(buff));	

	return true;
}

bool Network::sendConnect()
{
	uint8_t buff[MSG_HEADER_SIZE + sizeof(movementCommand_t) + me->getName().size()];

	movementCommand_t move;
	
	move.x = me->getPos().x;
	move.y = me->getPos().y;
	move.dirX = me->getDir().x;
	move.dirY = me->getDir().y;

	buff[0] = COMMAND_CONNECT;
	memcpy(&buff[1], &move, sizeof(move));
	memcpy(&buff[1 + sizeof(move)], me->getName().c_str(), me->getName().size());

	sendData(buff, sizeof(buff));

	return true;
}

