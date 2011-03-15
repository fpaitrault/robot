/*
 * motor_service.h
 *
 *  Created on: 25 janv. 2011
 *      Author: garfield
 */

#ifndef MOTOR_SERVICE_H_
#define MOTOR_SERVICE_H_

#include <pthread.h>
#include <IceBox/IceBox.h>

class motorServiceI : public IceBox::Service {
public:
	virtual void start(const std::string&,
			const Ice::CommunicatorPtr&,
			const Ice::StringSeq&);
	virtual void stop();
private:
    Ice::ObjectAdapterPtr _adapter;
};

#endif /* MOTOR_SERVICE_H_ */
