/*


	Server for bubble chat project
	Author: Rytis KarpuŠka
		rytis@elektromotus.lt

*/

#include <stdlib.h>
#include <pthread.h>

#include "mutex.h"

Mutex::Mutex()
{
	pthread_mutex_init(&mutex, NULL);

	return;
}

void Mutex::lock()
{
	pthread_mutex_lock(&mutex);

	return;
}

void Mutex::unlock()
{
	pthread_mutex_unlock(&mutex);

	return;
}


