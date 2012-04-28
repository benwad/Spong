/*
 *  Collidable.h
 *  teapots
 *
 *  Created by Ben Wadsworth on 26/07/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "structs.h"

class Collidable {
protected:
	Vectorxyz location, size;
public:
	void setLocation(float locx, float locy, float locz);
	void setSize(float _sizex, float _sizey, float _sizez);
	Vectorxyz getSize();
	Vectorxyz getLocation();
	Rectangle getRectangle();
};

#endif