/*
 *  Collidable.cpp
 *  teapots
 *
 *  Created by Ben Wadsworth on 26/07/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Collidable.h"

void Collidable::setLocation(float _locx, float _locy, float _locz) {
	location.x = _locx;
	location.y = _locy;
	location.z = _locz;
}

void Collidable::setSize(float _sizex, float _sizey, float _sizez) {
	size.x = _sizex;
	size.y = _sizey;
	size.z = _sizez;
}

Vectorxyz Collidable::getSize() {
	return size;
}

Vectorxyz Collidable::getLocation() {
	return location;
}

Rectangle Collidable::getRectangle() {
	Rectangle rectangle;
	Vectorxyz max, min;
	max.x = (location.x + size.x/2.0f);
	max.y = (location.y + size.y/2.0f);
	max.z = (location.z + size.z/2.0f);
	
	min.x = (location.x - size.x/2.0f);
	min.y = (location.y - size.y/2.0f);
	min.z = (location.z - size.z/2.0f);
	
	rectangle.max = max;
	rectangle.min = min;
	
	return rectangle;
}