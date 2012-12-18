/*


	Server for bubble chat project
	Author: Rytis KarpuŠka
		rytis@elektromotus.lt

*/

#ifndef _CLIENTS_H_
#define _CLIENTS_H_

#include <vector>
#include "moveType.h"
#include "mutex.h"

using namespace std;

class client {
private:
	movementCommand_t move;
	int id;
	char *name;
	

public:
	client(int id, movementCommand_t move, char *name);

	movementCommand_t getMove();
	void setMove(movementCommand_t move);
	int getID();
	char *getName();

};


class clients {
private:
	vector<client> clientVec;

public:
	
	void addClient(client c);
	void remClient(int id);
	client *at(int i);
	client *findByName(char *name);
	client *findByID(int id);
	
};


#endif
