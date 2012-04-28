/*
 *  Player.cpp
 *  teapots
 *
 *  Created by Ben Wadsworth on 23/07/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <math.h>
#include "Player.h"

Player::Player(float _locx, float _locy, float _locz) {
    location = Vectorxyz();
	location.x = _locx;
	location.y = _locy;
	location.z = _locz;
	speed = 0.0f;
	score = 0;
	size.x = 0.1f;
	size.y = 0.5f;
	size.z = 0.1f;
	health = 50.0f;
	colour.r = 0.0f;
	colour.g = 1.0f;
	colour.b = 0.0f;
}

Player::~Player() {
	delete &location;
	delete &speed;
	delete &size;
	delete &score;
	delete &colour;
}

void Player::updateLocation() {
	if ((location.y < -2.0f) && (speed < 0.0f)) {
		stop();
	} else if ((location.y > 2.0f) && (speed > 0.0f)) {
		stop();
	} else {
		location.y += speed;
	}
	if (health > 0) {
		colour.r = 1-(health/50.0f);
		colour.g = health/50.0f;
		colour.b = 0.0f;
	} else {
		colour.r *= 0.8f;
		colour.g *= 0.8f;
		colour.b *= 0.8f;
	}
}

void Player::stop() {
	speed = 0.0f;
}

void Player::moveUp(float _speed) {
	speed = _speed;
}

void Player::moveDown(float _speed) {
	speed = -(_speed);
}

void Player::scorePoints(int _points) {
	score += _points;
}

void Player::resetScore() {
	score = 0;
}

int Player::getScore() {
	return score;
}

float Player::getSpeed() {
	return speed;
}

void Player::applyDamage(int rotationSpeed) {
	health -= abs(rotationSpeed);
}

void Player::resetHealth() {
	health = 50;
}

int Player::getHealth() {
	return health;
}

RGBColour Player::getColour() {
	return colour;
}

void Player::resetPosition(float x, float y, float z) {
	location.x = x;
	location.y = y;
	location.z = z;
}
