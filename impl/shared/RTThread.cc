/*
 * RTThread.cc
 *
 *  Created on: 10 févr. 2011
 *      Author: garfield
 */

#include <stdio.h>
#include <errno.h>
#include "RTThread.h"

void *callback(void *arg)
{
	static_cast<Robot::RTThread*>(arg)->run();
}
namespace Robot {

RTThread::RTThread(int priority, int period )
{
	sp_.__sched_priority = priority;
	period_ = period;
	end_ = false;
	clock_gettime(CLOCK_MONOTONIC, &nextTs_);

	pthread_attr_init(&attr_);
	pthread_attr_setschedpolicy(&attr_, SCHED_FIFO);
	pthread_attr_setschedparam(&attr_, &sp_);
	pthread_create(&th_, &attr_, callback, this);

}
void RTThread::run()
{
	while(!end_)
	{
		//Wait next period
		while ( clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &nextTs_, NULL) != 0 && errno == EINTR )
		{
			errno = 0;
		}
		//Calculate next period
		timespec lastTS = nextTs_;
		nextTs_.tv_nsec = (lastTS.tv_nsec + period_*1000)%1000000000;
		nextTs_.tv_sec += (lastTS.tv_nsec + period_*1000)/1000000000;

		//Call update method
		update();
	}
}
RTThread::~RTThread()
{
	end_ = true;
	pthread_join(th_,0);
}

}
