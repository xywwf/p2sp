/*
 * queue.h
 *
 *  Created on: 2015年11月17日
 *      Author: wrb00_000
 */

#ifndef CUBE_SERVICE_UTIL_LINUX_QUEUE_H_
#define CUBE_SERVICE_UTIL_LINUX_QUEUE_H_
#include <iostream>
#include <errno.h>
#include <semaphore.h>
#include "cube/service/stdns.h"
BEGIN_SERVICE_NS
/*
 *	read write queue which is thread safe for only one reader & writer.
 *no lock used, it has high performance. it work best if make sure the
 *reader is faster than the writer
 *
 *	!!notes!!:
 *	please adjust "queue size" for a good performance under different
 *platform with different hardware, like: CPU.
 */
template<class type>
class queue {
public:
	queue();
	queue(unsigned long qsz);
	virtual ~queue();

	/*
	 *	initialize the queue with queue size @qsz
	 *@param qsz: queue size
	 *return:
	 *	0--success, -1--failed
	 */
	int init(unsigned long qsz);

	/*
	 *	read a value from queue in block mode until read success
	 *@param ptr: in & out pointer to the read value
	 *return:
	 *	0--always success, -1--failed
	 */
	int read(type *ptr, int waittm = -1);

	/*
	 *	write a value to the queue in block mode until write success
	 *@param ptr: pointer value to write
	 *return:
	 *	0--always success, -1--failed
	 */
	int write(type ptr, int waittm = -1);

	/*
	 *	read a value from queue in non-block mode
	 *@param ptr: point to value if there is readable value in the queue
	 *return:
	 *	0--success, -1--no value has read, must wait
	 */
	int _read(type *ptr);

	/*
	 *	write a value into the queue in non-block mode
	 *@param ptr: value to write
	 *return:
	 *	0--success, -1--no space can be used, must wait
	 */
	int _write(type ptr);

public:
	/*
	 *	get the elements number in the queue
	 */
	unsigned int size() {
		volatile unsigned int num = _wpos - _rpos;
		return num;
	}

private:
	/*
	 *	get a future time @tm by @elapse million sec
	 */
	int get_waittm(struct timespec *tw, int elapse);

	/*
	 *	expends a @val to power of 2. for example: 3->4, 7->8, 12->16, 21->32
	 */
	unsigned long roundup_power_of_two(unsigned long val);

private:
	//queue size
	unsigned long _qsize;

	//queue array
	type* _queue;

	//wait flag for read operation
	volatile long _rwflag;

	//wait flag for write operation
	volatile long _wwflag;

	//current read position of queue array
	volatile unsigned long _rpos;

	//next write position of queue array
	volatile unsigned long _wpos;

	//wait condition when read position catch the write position
	sem_t _cond1;
	//wait condition when write position catch the read position
	sem_t _cond2;
};
END_SERVICE_NS
#endif /* CUBE_SERVICE_EPOLL_QUEUE_H_ */
