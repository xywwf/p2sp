#ifndef CUBE_THREAD_LINUX_TYPE_H_
#define CUBE_THREAD_LINUX_TYPE_H_
#include <pthread.h>
#include <semaphore.h>
#include "cube/thread/stdns.h"

BEGIN_THREAD_NS
typedef pthread_mutex_t condition_mutex_t;
typedef pthread_cond_t condition_t;

typedef pthread_mutex_t critical_section_t;
typedef pthread_mutex_t mutex_t;
typedef pthread_rwlock_t rwlock_t;
typedef sem_t semaphore_t;
typedef pthread_t thread_t;
END_THREAD_NS

#ifndef __thread_return
#define __thread_return void*
#endif

#endif /* CUBE_THREAD_LINUX_TYPE_H_ */
