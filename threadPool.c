//included libraries
#include "threadPool.h"
#include <unistd.h>
#include <stdlib.h>
//defines
#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAIL -1
#define STDERR 2
#define KILL 0
#define WAIT 1
#define REG 2
#define ALL_GOOD 1
#define BAD_OR_IN_PROGRESS 0
//Returns length of inputed string
int stringLen(const char* str)
{
	int i = 0;
	while (str[i])
	{
		++i;
	}
	return i;
}
//deallocates ThreadPool and its inner resources
void deAllocThreadPool(ThreadPool* tp)
{
	OSQueue* queue = NULL;
	if (tp)
	{
		if (tp->task_handlers)
		{
			free(tp->task_handlers);
			tp->task_handlers = NULL;
		}
		if (tp->task_queue)
		{
			queue = tp->task_queue;
			while (!osIsQueueEmpty(queue))	//deAllocate all tasks, if there are still left...
			{
				free(osDequeue(queue));
			}
			free(tp->task_queue);
			tp->task_queue = NULL;
		}
		if (tp->paramsForHandlers)
		{
			free(tp->paramsForHandlers);
			tp->paramsForHandlers = NULL;
		}
		tp->numOfHandlers = 0;
		free(tp);
	}
}
void* taskHandler(void* args)
{
	int* mode = NULL;
	OSQueue* task_queue = NULL;
	Task* task = NULL;
	//extract condition variable and mutex and wait for all handlers to be ready...
	taskHandlerParams* params = (taskHandlerParams*) args;
	pthread_cond_t* cond_var = params->cond_var;
	pthread_mutex_t* lock = params->lock;
	pthread_cond_wait(cond_var, lock);
	//check if creation went bad...
	if (!(*(params->creation_status)))
	{
		pthread_mutex_unlock(lock);
		return NULL;
	}
	//extract rest of arguments...
	mode = params->mode;
	task_queue = params->task_queue;
	while (TRUE)
	{
		if (osIsQueueEmpty(task_queue))
		{
			if (*mode == WAIT) //case ThreadPool being destructed and Queue needs to be cleared
			{
				while (!osIsQueueEmpty(task_queue))
				{	//as long as queue isn't empty, extract tasks and execute them...
					task = (Task*) osDequeue(task_queue);
					pthread_mutex_unlock(lock);
					task->computeFunc(task->params);
					free(task);
					pthread_mutex_lock(lock);
				}
				pthread_mutex_unlock(lock);
				break;
			}
			if (*mode == KILL) //case immediate destruction was called
			{
				pthread_mutex_unlock(lock);
				break;
			}
			pthread_cond_wait(cond_var, lock); //well, no Tasks, lets go to sleep...
		}
		else //not empty...
		{
			if (*mode == WAIT) //case during destruction, but Queue needs to be cleared
			{
				while (!osIsQueueEmpty(task_queue))
				{	//as long as queue isn't empty, extract tasks and execute them...
					task = (Task*) osDequeue(task_queue);
					pthread_mutex_unlock(lock);
					task->computeFunc(task->params);
					free(task);
					pthread_mutex_lock(lock);
				}
				pthread_mutex_unlock(lock);
				break;
			}
			if (*mode == KILL) //case immediate destruction was called
			{
				pthread_mutex_unlock(lock);
				break;
			}
			//*mode == REG, case we're in regular mode, execute the Task and check if another is ready
			task = (Task*) osDequeue(task_queue);	//extract task and execute it
			pthread_mutex_unlock(lock);
			task->computeFunc(task->params);
			free(task);
			pthread_mutex_lock(lock);
		}
	}
	return NULL;
}
//create ThreadPool
ThreadPool* tpCreate(int numOfThreads)
{
	const char* toPrint = NULL;
	pthread_mutex_t* lock = NULL;
	int i = 0, j = 0;
	ThreadPool* toRet = (ThreadPool*) malloc(sizeof(ThreadPool));
	if (!toRet)	//case allocation of ThreadPool fails...
	{
		toPrint = "Error in system call\n";
		write(STDERR, toPrint, stringLen(toPrint));
		return NULL;
	}
	toRet->destroyed = FALSE;
	toRet->mode = REG;
	toRet->creation_status = BAD_OR_IN_PROGRESS;
	toRet->numOfHandlers = numOfThreads;
	toRet->task_handlers = (pthread_t*) malloc(sizeof(pthread_t) * numOfThreads);
	toRet->paramsForHandlers = (taskHandlerParams*) malloc(sizeof(taskHandlerParams) * numOfThreads);
	toRet->task_queue = osCreateQueue();
	if (!toRet->task_handlers || !toRet->task_queue || !toRet->paramsForHandlers)
	{	//case allocation of ThreadPool fields fails...
		toPrint = "Error in system call\n";
		write(STDERR, toPrint, stringLen(toPrint));
		deAllocThreadPool(toRet);
		return NULL;
	}
	if (pthread_mutex_init(&toRet->lock, NULL))
	{	//case initialization of mutex fails...
		toPrint = "Error in system call\n";
		write(STDERR, toPrint, stringLen(toPrint));
		deAllocThreadPool(toRet);
		return NULL;
	}
	if (pthread_cond_init(&toRet->cond_var, NULL))
	{	//case initialization of condition variable fails...
		toPrint = "Error in system call\n";
		write(STDERR, toPrint, stringLen(toPrint));
		pthread_mutex_destroy(&toRet->lock);
		deAllocThreadPool(toRet);
		return NULL;
	}
	lock = &toRet->lock;
	for (; i < numOfThreads; ++i)
	{
		toRet->paramsForHandlers[i].cond_var = &toRet->cond_var;
		toRet->paramsForHandlers[i].lock = &toRet->lock;
		toRet->paramsForHandlers[i].task_queue = toRet->task_queue;
		toRet->paramsForHandlers[i].creation_status = &toRet->creation_status;
		toRet->paramsForHandlers[i].mode = &toRet->mode;
		pthread_mutex_lock(lock);	//to be unlocked by new born thread when he waits for creation to end...
		if(pthread_create(&toRet->task_handlers[i], NULL, &taskHandler, (void*) &toRet->paramsForHandlers[i]))
		{
			toPrint = "Error in system call\n";
			write(STDERR, toPrint, stringLen(toPrint));
			pthread_cond_broadcast(&toRet->cond_var);	//tell already created handlers to "die"...
			pthread_mutex_unlock(lock); //handlers need it in order to wake up and "die"...
			for (; j < i; ++j)
			{
				pthread_join(toRet->task_handlers[j], NULL);
			}
			pthread_mutex_destroy(&toRet->lock);
			pthread_cond_destroy(&toRet->cond_var);
			deAllocThreadPool(toRet);
			return NULL;
		}
	}
	toRet->creation_status = ALL_GOOD;
	pthread_cond_broadcast(&toRet->cond_var);
	pthread_mutex_lock(lock);	//request lock in order to be sure all handler threads are sleeping
	pthread_mutex_unlock(lock); //waiting for incoming tasks, thus are ready to work...
	return toRet;
}
//insert task to be executed by a ThreadPool task handler
int tpInsertTask(ThreadPool* threadPool, void (*computeFunc) (void *), void* param)
{
	const char* toPrint = NULL;
	Task* task = NULL;
	pthread_mutex_t* lock = &threadPool->lock;
	pthread_mutex_lock(lock);
	if (threadPool->destroyed)
	{
		pthread_mutex_unlock(lock);
		return FAIL;
	}
	else	//add task to queue
	{
		pthread_mutex_unlock(lock);
		task = (Task*) malloc(sizeof(Task));	//build task
		if (!task)
		{
			toPrint = "Error in system call\n";
			write(STDERR, toPrint, stringLen(toPrint));
			return FAIL;
		}
		task->computeFunc = computeFunc;
		task->params = param;
		pthread_mutex_lock(&threadPool->lock);
		osEnqueue(threadPool->task_queue, (void*) task);	//add task to queue
		pthread_cond_broadcast(&threadPool->cond_var);	//notify all handlers a task was added to queue
		pthread_mutex_unlock(&threadPool->lock);
		return SUCCESS;
	}
}
//destroy ThreadPool
void tpDestroy(ThreadPool* threadPool, int shouldWaitForTasks)
{
	pthread_cond_t* cond_var = NULL;
	pthread_t* handlers = NULL;
	int numThreads = 0, i = 0;
	pthread_mutex_t* lock = &threadPool->lock;
	pthread_mutex_lock(lock);
	if (threadPool->destroyed)	//case destroy was already called...
	{
		pthread_mutex_unlock(lock);
		return;
	}
	else	//destroy pool
	{
		threadPool->destroyed = TRUE;
		pthread_mutex_unlock(lock);
		if (!shouldWaitForTasks)
		{	//destroy immediately...
			threadPool->mode = KILL;
		}
		else
		{	//destroy while clearing the queue...
			threadPool->mode = WAIT;
		}
		cond_var = &threadPool->cond_var;
		pthread_cond_broadcast(cond_var);
		numThreads = threadPool->numOfHandlers;
		handlers = threadPool->task_handlers;
		for (; i < numThreads; ++i)
		{	//wait for all handler threads to "die"
			pthread_join(handlers[i], NULL);
		}
		//destroy condition variable and mutex
		pthread_mutex_destroy(lock);
		pthread_cond_destroy(cond_var);
		deAllocThreadPool(threadPool);
	}
}
