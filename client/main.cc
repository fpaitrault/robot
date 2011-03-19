/*
 * main.cc
 *
 *  Created on: 27 janv. 2011
 *      Author: garfield
 */
#include <iostream>
#include <Ice/Ice.h>
#include "hardware.h"
using namespace std;
//-----------------------------------------------------------------------------
class RobotClient : public Ice::Application
{
public:

    RobotClient();

    virtual int run(int, char*[]);

private:

    void menu();
};
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    RobotClient app;
    return app.main(argc, argv);
}
//-----------------------------------------------------------------------------
RobotClient::RobotClient() :
    //
    // Since this is an interactive demo we don't want any signal
    // handling.
    //
    Ice::Application(Ice::NoSignalHandling)
{
}
//-----------------------------------------------------------------------------
int RobotClient::run(int argc, char* argv[])
{
    if(argc > 1)
    {
        cerr << appName() << ": too many arguments" << endl;
        return EXIT_FAILURE;
    }

    hardware::motorPrx motors = hardware::motorPrx::checkedCast(
        communicator()->stringToProxy("Motors:tcp -h 192.168.0.12 -p 10001"));

//    motors->move(150);
//    motors->rotate(90);
//    motors->rotate(-90);
//    motors->move(-150);
}
//-----------------------------------------------------------------------------
