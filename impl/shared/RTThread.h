/*
 * RTThread.h
 *
 *  Created on: 10 févr. 2011
 *      Author: garfield
 */

#ifndef RTTHREAD_H_
#define RTTHREAD_H_

#include <pthread.h>
#include <time.h>


namespace Robot {

class RTThread {
private:
	pthread_t th_;
	pthread_attr_t attr_;
	sched_param sp_;
	bool end_;
	int period_;
	timespec nextTs_;
public:
	RTThread(int priority, int period);
	virtual ~RTThread();
	void run();
	virtual void update() = 0;
};

}

#endif /* RTTHREAD_H_ */
