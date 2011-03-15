/*
 * motorSerial.cc
 *
 *  Created on: 2 févr. 2011
 *      Author: garfield
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "motorSerial.h"
#define BAUDRATE B38400
#define DEVICE "/dev/ttySAC1"
const char GETSPEED1_CMD[2]  = {0x0, 0x21};
const char GETSPEED2_CMD[2]  = {0x0, 0x22};
const char GETENCODERS_CMD[2]= {0x0, 0x25};
const char GETVI_CMD[2]      = {0x0, 0x2C};
const char SETSPEED1_CMD[2]  = {0x0, 0x31};
const char SETSPEED2_CMD[2]  = {0x0, 0x32};
const char RSTENCDRS_CMD[2]  = {0x0, 0x35};
const char SETMODE_CMD[3]  = {0x0, 0x34, 0x02};
namespace Robot
{
//-----------------------------------------------------------------------------
motorSerial::motorSerial() : stopRequested_(false)
{
	struct termios newtio;
	fd_ = open(DEVICE, O_RDWR | O_NOCTTY | O_NONBLOCK);
	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag = BAUDRATE | CS8 | CSTOPB;
	newtio.c_iflag = IGNPAR | ICRNL;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;
	tcflush(fd_, TCIOFLUSH);
	tcsetattr(fd_,TCSANOW,&newtio);

	//Reset encoders
	write(fd_, RSTENCDRS_CMD, sizeof(RSTENCDRS_CMD));
	//Set Moving mode
	write(fd_, SETMODE_CMD, sizeof(SETMODE_CMD));
}
//-----------------------------------------------------------------------------
motorSerial::~motorSerial()
{
	close(fd_);
}
//-----------------------------------------------------------------------------
void motorSerial::readParameter(const char *cmd, unsigned long cmdSize,
		void *resp, unsigned long respSize)
{
	ssize_t nBytes = 0;
	int counter = 1000;
	write(fd_, cmd, cmdSize);
	while(nBytes < respSize && counter > 0){
		nBytes += read(fd_, (char*)resp+nBytes, respSize);
		counter--;
		usleep(1000); //Wait 1ms
//			printf("[ ");
//			for(unsigned short i=0;i<nBytes;i++)
//				printf("%02X ",((char*)resp)[i]);
//			printf("]\n");
	}
//	printf("[ ");
//	for(unsigned short i=0;i<respSize;i++)
//		printf("%02X ",((char*)resp)[i]);
//	printf("]\n");
}
//-----------------------------------------------------------------------------
sVIInfo motorSerial::retrieveVI()
{
	sVIInfo infos;
	readParameter(GETVI_CMD, sizeof(GETVI_CMD), &infos, sizeof(infos));
	return infos;
}
//-----------------------------------------------------------------------------
sEncInfo motorSerial::retrieveEnc()
{
	sEncInfo infos;
	readParameter(GETENCODERS_CMD, sizeof(GETENCODERS_CMD), &infos, sizeof(infos));
	//Convert big to little endian
	infos.encoder1 = be32toh(infos.encoder1);
	infos.encoder2 = be32toh(infos.encoder2);
	return infos;
}
//-----------------------------------------------------------------------------
long motorSerial::retrieveSpeed1()
{
	int8_t speed;
	readParameter(GETSPEED1_CMD, sizeof(GETSPEED1_CMD), &speed, 1);
	return speed;
}
//-----------------------------------------------------------------------------
long motorSerial::retrieveSpeed2()
{
	int8_t speed;
	readParameter(GETSPEED2_CMD, sizeof(GETSPEED2_CMD), &speed, 1);
	return speed;
}
//-----------------------------------------------------------------------------
void motorSerial::setSpeed(int8_t speed1, int8_t speed2)
{
	char cmd[3];
	memcpy(cmd, SETSPEED1_CMD, sizeof(SETSPEED1_CMD));
	cmd[2] = speed1;
	write(fd_, cmd, 3);
	memcpy(cmd, SETSPEED2_CMD, sizeof(SETSPEED2_CMD));
	cmd[2] = speed2;
	write(fd_, cmd, 3);
}
//-----------------------------------------------------------------------------
};
