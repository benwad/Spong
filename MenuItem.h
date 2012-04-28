/*
 *  MenuItem.h
 *  teapots
 *
 *  Created by Ben Wadsworth on 14/08/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MENUITEM_H
#define MENUITEM_H

#define RESPONSE_NULL 0
#define RESPONSE_OPEN_SUBMENU 1
#define RESPONSE_PLAY_1P 2
#define RESPONSE_PLAY_2P 3
#define RESPONSE_CONTROLS 4
#define RESPONSE_QUIT 5

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include "drawText.h"

class MenuItem {
protected:
	std::vector<MenuItem*> children;
	std::string name;
	float xsize, ysize;
	int response;
	bool focused;
	std::string imageFile;
	GLuint texture;
public:
	MenuItem(std::string name);
	void drawAt(float,float);
	void setSize(float,float);
	void setFocused(bool);
	void addChild(MenuItem*);
	void setResponse(int);
	void setImage(std::string filename);
	std::vector<MenuItem*> getChildren();
	int getResponse();
	bool getFocused();
	float getXSize();
	float getYSize();
	std::string getName();
};

#endif