/*
 *  Ball.cpp
 *  teapots
 *
 *  Created by Ben Wadsworth on 26/07/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdlib.h>
#include "Ball.h"

Ball::Ball(float _locx, float _locy, float _locz) {
	location.x = 0.0f;
	location.y = 0.0f;
	location.z = 0.0f;
	speedx = -0.05f;
	speedy = -0.02f;
	size.x = 0.1f;
	size.y = 0.1f;
	size.z = 0.1f;
	serve = 1;
}

void Ball::resetPosition() {
	location.x = 0.0f;
	location.y = 0.0f;
	location.z = 0.0f;
	rotationSpeed = 0.0f;
	rotationAmount = 0.0f;
	if (serve == 1) {
		speedx = -0.05f;
		speedy = -0.02f;
	} else {
		speedx = 0.05f;
		speedy = 0.02f;
	}
	
}

void Ball::updateLocation() {
	location.x += speedx;
	location.y += speedy;
	rotationAmount += rotationSpeed;
	if (rotationAmount > 360) {
		rotationAmount -= 360;
	} else if (rotationAmount < 0) {
		rotationAmount += 360;
	}
	
	/*
	if (abs(speedx) == speedx) {
		speedx += abs(rotationSpeed / 50000.0f);
	} else {
		speedx += abs(rotationSpeed / 50000.0f);
	}
	 */
	
	speedy -= rotationSpeed / 100000.0f;
}

void Ball::setSpeed(float x, float y) {
	speedx = x;
	speedy = y;
}

void Ball::invertx() {
	speedx = -speedx;
}

void Ball::inverty() {
	speedy = -speedy;
}

void Ball::setServe(int _serve) {
	serve = _serve;
}

float Ball::getSpeedX() {
	return speedx;
}

float Ball::getSpeedY() {
	return speedy;
}

void Ball::addClockwiseRotation() {
	rotationSpeed -= 10.0f;
	speedx *= 1.05f;
}

void Ball::addAntiClockwiseRotation() {
	rotationSpeed += 10.0f;
	speedx *= 1.05f;
}

void Ball::invertRotation() {
	rotationSpeed = -rotationSpeed;
}

void Ball::resetRotation() {
	rotationSpeed = 0.0f;
	rotationAmount = 0.0f;
}

float Ball::getRotationAmount() {
	return rotationAmount;
}

float Ball::getRotationSpeed() {
	return rotationSpeed;
}