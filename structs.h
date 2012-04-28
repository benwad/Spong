/*
 *  structs.h
 *  teapots
 *
 *  Created by Ben Wadsworth on 26/07/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef STRUCTS_H
#define STRUCTS_H

struct Vectorxyz {
	float x;
	float y;
	float z;
};

struct Rectangle {
	Vectorxyz max;
	Vectorxyz min;
};

struct RGBColour {
	float r;
	float g;
	float b;
};

#endif