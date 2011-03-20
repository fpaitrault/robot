/*
 * motorControl.h
 *
 *  Created on: 10 févr. 2011
 *      Author: garfield
 */

#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

#include "RTThread.h"
#include "../serial/motorSerial.h"

namespace Robot
{
enum eMoveType
{
	eMoveType_None,
	eMoveType_Translate,
	eMoveType_Rotate,
};

class motorControl : public RTThread
{
private:
	sEncInfo currEnc_, reqEnc_;
	long reqSpeed_;
	eMoveType type_;
	motorSerial serial_;
public:
	motorControl();
	void init();
	void update();

	void translate(long distance);
	void rotate(long angle);

};

};

#endif /* MOTORCONTROL_H_ */
