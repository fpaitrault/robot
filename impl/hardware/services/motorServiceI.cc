/*
 * motor_service.cc
 *
 *  Created on: 25 janv. 2011
 *      Author: garfield
 */
#include <pthread.h>
#include <Ice/Ice.h>
#include "motorServiceI.h"
#include "motorI.h"

using namespace std;

void motorServiceI::start(
    const string& name,
    const Ice::CommunicatorPtr& communicator,
    const Ice::StringSeq& args)
{
    _adapter = communicator->createObjectAdapter(name);
    Ice::ObjectPtr object = new Robot::motorI();
    _adapter->add(object, communicator->stringToIdentity("Motors"));
    _adapter->activate();
}

void motorServiceI::stop()
{
    _adapter->deactivate();
}

extern "C" {
    IceBox::Service* create(Ice::CommunicatorPtr communicator)
    {
        return new motorServiceI;
    }
}

