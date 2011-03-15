/*
 * motorI.h
 *
 *  Created on: 26 janv. 2011
 *      Author: garfield
 */

#ifndef MOTORI_H_
#define MOTORI_H_

#include "motor.h"
#include "impl/control/motorControl.h"

namespace Robot
{
class motorI : public robot::motor
{
protected:
	motorControl control_;
	int fd_;
public:
	motorI(void);
	void move(Ice::Long distance, const Ice::Current& current);
	void rotate(Ice::Long angle, const Ice::Current& current);
	Ice::Long measure(const Ice::Current& current);
};
};
#endif /* MOTORI_H_ */
