/*
 * motorSerial.h
 *
 *  Created on: 2 févr. 2011
 *      Author: garfield
 */

#ifndef motorSerial_H_
#define motorSerial_H_

#include <sys/types.h>

struct sVIInfo
{
	unsigned short voltage : 8;
	unsigned short current1 : 8;
	unsigned short current2 : 8;
};
struct sEncInfo
{
	long encoder1;
	long encoder2;
};
namespace Robot
{
class motorSerial
{
public:
	motorSerial();
	~motorSerial();
	void setSpeed(int8_t speed1, int8_t speed2);
	sVIInfo retrieveVI();
	sEncInfo retrieveEnc();
	long retrieveSpeed1();
	long retrieveSpeed2();

protected:
    int fd_;
    bool stopRequested_;
private:
    void readParameter(const char *cmd, unsigned long cmdSize,
    		void *resp, unsigned long respSize);
};
};

#endif /* motorSerial_H_ */
