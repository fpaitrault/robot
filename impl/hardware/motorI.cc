/*
 * motorI.cc
 *
 *  Created on: 26 janv. 2011
 *      Author: garfield
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include "motorI.h"

#define DEVICE "/dev/ttySAC2"
#define BAUDRATE B9600

using namespace std;
namespace Robot
{
//-----------------------------------------------------------------------------
motorI::motorI() : control_()
{
	control_.init();
}
//-----------------------------------------------------------------------------
void motorI::move(Ice::Long distance, const Ice::Current& current)
{
	control_.translate(distance);
}
//-----------------------------------------------------------------------------
void motorI::rotate(Ice::Long angle, const Ice::Current& current)
{
	control_.rotate(angle);
}
//-----------------------------------------------------------------------------
Ice::Long motorI::measure(const Ice::Current& current)
{
	Ice::Long result;
	char buffer[5];
	int i=0;
	struct termios newtio;
	fd_ = open(DEVICE, O_RDWR | O_NOCTTY);

    fcntl(fd_, F_SETFL, 0);
    // set everything to 0
    bzero(&newtio, sizeof(newtio));

    // again set everything to 0
    bzero(&newtio, sizeof(newtio));

    newtio.c_cflag |= BAUDRATE; // Set Baudrate first time
    newtio.c_cflag |= CLOCAL; // Local line - do not change "owner" of port
    newtio.c_cflag |= CREAD; // Enable receiver

    newtio.c_cflag &= ~ECHO; // Disable echoing of input characters
    newtio.c_cflag &= ~ECHOE;

    // set to 8N1
    newtio.c_cflag &= ~PARENB; // no parentybyte
    newtio.c_cflag &= ~CSTOPB; // 1 stop bit
    newtio.c_cflag &= ~CSIZE; // Mask the character size bits
    newtio.c_cflag |= CS8; // 8 data bits

    // output mode to
    newtio.c_oflag = 0;
    //newtio.c_oflag |= OPOST;


    // Set teh baudrate for sure
    cfsetispeed(&newtio, BAUDRATE);
    cfsetospeed(&newtio, BAUDRATE);

	tcflush(fd_, TCIOFLUSH);
	tcsetattr(fd_,TCSANOW,&newtio);
	while(i<1000)
	{
		i++;
		int nBytes = read(fd_,buffer,5);
		if(nBytes != 0)
		{
				printf("[ ");
				for(unsigned short i=0;i<nBytes;i++)
					printf("%02X ",((char*)buffer)[i]);
				printf("]\n");
		}
		usleep(10000);
	}
	close(fd_);
}
//-----------------------------------------------------------------------------

};

