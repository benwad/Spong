/*
 *  Ball.h
 *  teapots
 *
 *  Created by Ben Wadsworth on 26/07/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BALL_H
#define BALL_H

#include "Collidable.h"

class Ball : public Collidable {
	float speedx, speedy, rotationSpeed, rotationAmount;
	int serve;
public:
	Ball(float, float, float);
	void resetPosition();
	void setSpeed(float _speedx, float _speedy);
	void updateLocation();
	void invertx();
	void inverty();
	void addClockwiseRotation();
	void addAntiClockwiseRotation();
	void invertRotation();
	void resetRotation();
	void setServe(int _serve);
	float getRotationAmount();
	float getRotationSpeed();
	float getSpeedX();
	float getSpeedY();
	float getLocX();
	float getLocY();
};

#endif