/*


	Server for bubble chat project
	Author: Rytis KarpuŠka
		rytis@elektromotus.lt

*/

#include <stdlib.h>
#include <string.h>
#include "clients.h"
#include "server.h"

client::client(int _id, movementCommand_t _move, char *_name)
{
	//allocate memory and copy string
	char *myName = (char *)malloc(strlen(_name) + 1);
	strcpy(myName, _name);

	name = myName;
	id = _id;
	move = _move;

	return;
}

char *client::getName()
{
	return name;
}

int client::getID()
{
	return id;
}

movementCommand_t client::getMove()
{
	return move;
}

void client::setMove(movementCommand_t _move)
{
	move = _move;
}

void clients::addClient(client c)
{
	clientVec.push_back(c);
}

void clients::remClient(int id)
{
	int i;
	for(i = 0; i < clientVec.size(); i++){
		if(clientVec[i].getID() == id)
			break;
	}

	if(i < clientVec.size()){
		clientVec[i] = clientVec[clientVec.size() - 1];
		clientVec.erase(--clientVec.end());
	}

	return;
}

client *clients::at(int i)
{
	if(i < 0 || i >= clientVec.size())
		return NULL;

	return &clientVec[i];
}

client *clients::findByName(char *name)
{
	for(int i = 0; i < clientVec.size(); i++)
		if(strcmp(name, clientVec[i].getName()) == 0)
			return &clientVec[i];
	
	return NULL;
}

client *clients::findByID(int id)
{
	for(int i = 0; i < clientVec.size(); i++)
		if(clientVec[i].getID() == id)
			return &clientVec[i];

	return NULL;
}

