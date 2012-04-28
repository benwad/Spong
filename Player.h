/*
 *  Player.h
 *  teapots
 *
 *  Created by Ben Wadsworth on 23/07/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include "Collidable.h"

class Player : public Collidable {
	float speed;
	int score;
	int health;
	RGBColour colour;
public:
	Player(float, float, float);
	~Player();
	int getScore();
	void stop();
	void moveUp(float);
	void moveDown(float);
	void updateLocation();
	void scorePoints(int);
	void applyDamage(int);
	void resetHealth();
	void resetScore();
	void resetPosition(float,float,float);
	float getSpeed();
	RGBColour getColour();
	int getHealth();
};

#endif