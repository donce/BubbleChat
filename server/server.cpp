/*


	Server for bubble chat project
	Author: Rytis KarpuŠka
		rytis@elektromotus.lt

*/


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

#include "network.h"
#include "server.h"
#include "mutex.h"

using namespace std;

int main() {

	Network net;

	net.init();

	//network created its threads, all actions will be performet there
	while(true){
		sleep(1);
	}

	return 0;
}


