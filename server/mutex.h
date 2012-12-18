/*


	Server for bubble chat project
	Author: Rytis KarpuŠka
		rytis@elektromotus.lt

*/

#ifndef __MUTEX_H_
#define __MUTEX_H_


#include <pthread.h>


class Mutex {

private: 
	pthread_mutex_t mutex;

public:

	Mutex();

	void lock();
	void unlock();

};



#endif
