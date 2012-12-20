/*


	Server for bubble chat project
	Author: Rytis KarpuŠka
		rytis@elektromotus.lt

*/

#include <time.h>
#include <stdio.h>
#include "network.h"
#include "clients.h"
#include <sys/select.h>
#include <math.h>
#include "server.h"

Network::Network()
{
	maxClients = 0;
	socketfd = -1;
}

Network::~Network()
{
	int i;

	for(i = 0; i < clientFD.size(); i++)
		close(clientFD[i]);

	if(socketfd >= 0)
		close(socketfd);
}

void Network::sendData(int idx, uint8_t *data, int size)
{
	if(size > 1024)
		return;

	if(idx < 0 || idx >= clientFD.size())
		return;

	timespec time = {0, 10};
	nanosleep(&time, NULL);

	//check if our socket is still valid
	long int fd = clientFD[idx];

	clientStackMutex.lock();
	send(clientFD[idx], data, size, 0);
	clientStackMutex.unlock();


	return;
}

void Network::sendPos(int idx, int moveIdx, movementCommand_t move)
{
	if(idx < 0 || idx >= clientFD.size())
		return;

	uint8_t buff[MESSAGE_HEADER_SIZE + sizeof(move)];

	buff[0] = COMMAND_MOVE;
	buff[1] = moveIdx;
	memcpy(&buff[2], &move, sizeof(move));
	
	sendData(idx, buff, sizeof(buff));

	//wait while data is sent
	timespec time = {0, 100};
	nanosleep(&time, NULL);	

	return;
}

void Network::sendMsg(int idx, int id, char *msg)
{
	if(idx < 0 || idx >= clientFD.size())
		return;

	if(strlen(msg) <= 0 || strlen(msg) + 1 >= 1024 - MESSAGE_HEADER_SIZE)
		return;

	uint8_t buff[MESSAGE_HEADER_SIZE + strlen(msg) + 1];

	buff[0] = COMMAND_CHAT;
	buff[1] = id;
	memcpy(&buff[2], msg, strlen(msg) + 1);

	sendData(idx, buff, sizeof(buff));

	//wait while data is sent
	timespec time = {0, 10};
	nanosleep(&time, NULL);	

	return;
}

void Network::sendUser(int idx, client c)
{
	uint8_t buff[MESSAGE_HEADER_SIZE + sizeof(movementCommand_t) +
			sizeof(int) + strlen(c.getName()) + 1];

	buff[0] = COMMAND_USER;

	movementCommand_t move = c.getMove();
	memcpy(&buff[1], &move, sizeof(move));
	int id = c.getID();
	memcpy(&buff[1 + sizeof(move)], &id, sizeof(id));
	memcpy(&buff[1 + sizeof(move) + sizeof(id)], c.getName(), strlen(c.getName()));
	buff[1 + sizeof(move) + sizeof(id) + strlen(c.getName())] = 0;	

	sendData(idx, buff, sizeof(buff));

	return;
}

void Network::sendUserDel(int idx, int id)
{
	uint8_t buff[MESSAGE_HEADER_SIZE + sizeof(id)];

	buff[0] = COMMAND_DISCONNECT;
	
	memcpy(&buff[1], &id, sizeof(id));
	
	sendData(idx, buff, sizeof(buff));

	return;
}

void *Network::waitForConnection()
{
	printf("Waiting for connections\n");

	socklen_t len = sizeof(sAddr);
	int fd;
	while(true){		
		const timespec time = {0, 1000};
		nanosleep(&time, NULL);//Introduce gurad time

		if(clientFD.size() >= maxClients)
			continue;

		//accept connection
		if((fd = accept(socketfd, (sockaddr *)&sAddr, &len)) >= 0){
			printf("Client connected %s\n", inet_ntoa(sAddr.sin_addr));

			//set non-block for file descriptor
			fcntl(fd, F_SETFL, O_NONBLOCK); 

			//access to client stack must be sinchronized
			clientStackMutex.lock();
			clientFD.push_back(fd);
			clientStackMutex.unlock();
			
		} else {
			printf("connection problem: %s\n", strerror(errno));
		}



	}


	return NULL;
}

void Network::parseMovementCommand(int idx, int sockFD, uint8_t *buff, int size)
{
	printf("movement command\n");

	movementCommand_t move;
	memcpy(&move, &buff[1], sizeof(move));

	cls.findByID(sockFD)->setMove(move);

	//resend that move to all other clients
	for(int i = 0; i < numOfClients(); i++){
		if(i == idx)
			continue;

		sendPos(i, sockFD, move);
	}

	return;
}

void Network::parseChatCommand(int idx, int sockFD, uint8_t *buff, int size)
{
	printf("chat command\n");

	char *text = (char *)&buff[1];
	printf("text: %s\n", text);


	//check if we are close enough
	movementCommand_t mePos;
	movementCommand_t otherPos;

	for(int i = 0; i <  numOfClients(); i++){
		if(i == idx)
			continue;

/*		mePos = cls.at(idx)->getMove();
		otherPos = cls.at(i)->getMove();
		int diffX = abs(mePos.x - otherPos.y);
		int diffY = abs(mePos.y - otherPos.y);

		if(diffX > ALLOWED_DISTANCE ||
				diffY > ALLOWED_DISTANCE)
			continue;

*/		sendMsg(i, sockFD, text);
	}

	

	return;
}


void Network::parseDisconnectCommand(int idx, int sockFD, uint8_t *buff, int size)
{
	printf("disconnect command received\n");

	clientStackMutex.lock();
	clientFD[idx] = clientFD[clientFD.size() - 1];
	clientFD.erase(--clientFD.end());
	clientStackMutex.unlock();

	cls.remClient(sockFD);

	for(int i = 0; i < numOfClients(); i++){
		if(i == idx)
			continue;
		
		sendUserDel(i, sockFD);
	}

	return;
}


void Network::parseConnectCommand(int idx, int sockFD, uint8_t *buff, int size)
{
	printf("connect command received\n");

	//extract data from buffer
	movementCommand_t move;
	char *name;

	memcpy(&move, &buff[1], sizeof(move));
	name = (char *)&buff[1 + sizeof(move)];

	client *c = new client(sockFD, move, name);

	cls.addClient(*c);

	//send new user to all old users
	for(int i = 0; i < numOfClients(); i++){
		if(i == idx)
			continue;

		sendUser(i, *c);
	}

	//send all old users to new user
	for(int i = 0; i < numOfClients(); i++){
		if(cls.at(i)->getID() == sockFD)
			continue;

		sendUser(idx, *cls.at(i));
	}
	

	return;
}


void *Network::processTransmittedData()
{
	int size, fd;
	uint8_t buff[1024];
	vector<int> tmpFD;

	while(true){
		const timespec time = {0, 1000};
		nanosleep(&time, NULL);

		//initiate size
		clientStackMutex.lock();
		tmpFD = clientFD;
		clientStackMutex.unlock();
		
		for(int i = 0; i < tmpFD.size(); i++){
			if((size = recv(tmpFD[i], &buff, sizeof(buff), 0)) > 1){
				switch(buff[0]){
				case COMMAND_MOVE:
					parseMovementCommand(i, tmpFD[i], buff, size);
					break;

				case COMMAND_CHAT:
					parseChatCommand(i, tmpFD[i], buff, size);
					break;

				case COMMAND_DISCONNECT:
					parseDisconnectCommand(i, tmpFD[i], buff, size);
					break;
	
				case COMMAND_CONNECT:
					parseConnectCommand(i, tmpFD[i], buff, size);
					break;

				}

				memset(buff, 0, sizeof(buff));
			}

		}

	}

	return NULL;
}



static void *pthread_wrapperForTransmitData(void *args)
{
	return ((Network *)args)->processTransmittedData();
}

static void *pthread_wrapperForConnectionWait(void *args)
{
	return ((Network *)args)->waitForConnection();
}


bool  Network::init(int port, int _maxClients) {

	if(_maxClients < 0 || _maxClients > MAX_SUPPORTED_CLIENTS)
		return false;

	//save max clients 
	maxClients = _maxClients;

	//open network socket
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd == -1)
		return false;
	
	sAddr.sin_family = AF_INET;
	sAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sAddr.sin_port = htons(port);
	
	if(bind(socketfd, (sockaddr*)&sAddr, sizeof(sAddr)) == -1)
		return false;
	
	if(listen(socketfd, 10) != 0)
		fprintf(stderr, "%s\n", strerror(errno));

	pthread_t thread[NUM_OF_THREADS];

	//create data proccessing thread
	pthread_create(&thread[0], NULL, pthread_wrapperForTransmitData, this);
	pthread_create(&thread[1], NULL, pthread_wrapperForConnectionWait, this);

	return true;
}

int Network::numOfClients()
{
	return clientFD.size();
}


