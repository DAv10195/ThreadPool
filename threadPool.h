#ifndef __THREAD_POOL__
#define __THREAD_POOL__
//included libraries
#include <pthread.h>
#include "osqueue.h"
//Task struct
typedef struct task
{
	void (*computeFunc) (void *);
	void* params;
}Task;
//taskHandlerParams struct
typedef struct handlerParams
{
	pthread_mutex_t* lock;
	pthread_cond_t* cond_var;
	OSQueue* task_queue;
	int* creation_status;
	int* mode;
}taskHandlerParams;
//ThreadPool struct
typedef struct thread_pool
{
	pthread_mutex_t lock;
	pthread_cond_t cond_var;
	pthread_t* task_handlers;
	taskHandlerParams* paramsForHandlers;
	OSQueue* task_queue;
	int mode;
	int creation_status;
	int numOfHandlers;
	int destroyed;
}ThreadPool;
//create ThreadPool
ThreadPool* tpCreate(int numOfThreads);
//destroy ThreadPool
void tpDestroy(ThreadPool* threadPool, int shouldWaitForTasks);
//insert task to be executed by a ThreadPool task handler
int tpInsertTask(ThreadPool* threadPool, void (*computeFunc) (void *), void* param);

#endif
