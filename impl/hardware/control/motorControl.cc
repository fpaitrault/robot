/*
 * motorControl.cc
 *
 *  Created on: 10 févr. 2011
 *      Author: garfield
 */

#include <stdio.h>
#include <math.h>
#include <iostream>
#include "motorControl.h"
extern "C"
{
	#include "realtime/Controller.h"
}
using namespace std;
#define WHEEL_DIAM 100
#define WHEEL_DIST 228
#define ABS(x) (x<0?-x:x)
namespace Robot
{
//-----------------------------------------------------------------------------
motorControl::motorControl() : RTThread(99,1000)
{
}
//-----------------------------------------------------------------------------
void motorControl::init()
{
	reqEnc_ = serial_.retrieveEnc();
	type_ = eMoveType_None;
	Controller_initialize();
}
//-----------------------------------------------------------------------------
void motorControl::update()
{
	currEnc_ = serial_.retrieveEnc();

	//Fill model parameters
	Controller_U.r = reqEnc_.encoder1;
	Controller_U.y = currEnc_.encoder1;
	//Execute step
	Controller_step();

	//Retrieve resulting parameters
	reqSpeed_ = Controller_Y.u;

	//Send speed request to motor
	switch(type_)
	{
	case eMoveType_Translate:
		serial_.setSpeed(128+reqSpeed_,128);
		break;
	case eMoveType_Rotate:
		serial_.setSpeed(128,128+reqSpeed_);
		break;
	};
}
//-----------------------------------------------------------------------------
void motorControl::translate(long distance)
{
	reqEnc_.encoder1 = currEnc_.encoder1 + (360*distance)/(WHEEL_DIAM*M_PI);
	type_ = eMoveType_Translate;

	do {usleep(100000); } while(reqSpeed_ !=0);
	type_ = eMoveType_None;
}
//-----------------------------------------------------------------------------
void motorControl::rotate(long angle)
{
	double angDist = (angle*WHEEL_DIST*M_PI)/360;
	reqEnc_.encoder1 = currEnc_.encoder1 + (angle*WHEEL_DIST)/WHEEL_DIAM;
	type_ = eMoveType_Rotate;

	do {usleep(100000); } while(reqSpeed_ !=0);
	type_ = eMoveType_None;
}
};
