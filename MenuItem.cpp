/*
 *  MenuItem.cpp
 *  teapots
 *
 *  Created by Ben Wadsworth on 14/08/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "MenuItem.h"

MenuItem::MenuItem(std::string _name) {
	response = RESPONSE_NULL;
	name = _name;
	focused = false;
	xsize = 0.5f;
	ysize = 0.1f;
}

void MenuItem::setSize(float x, float y) {
	xsize = x;
	ysize = y;
}

void MenuItem::setFocused(bool _focused) {
	focused = _focused;
}

bool MenuItem::getFocused() {
	return focused;
}

float MenuItem::getXSize() {
	return xsize;
}

float MenuItem::getYSize() {
	return ysize;
}

std::string MenuItem::getName() {
	return name;
}

void MenuItem::drawAt(float x, float y) {
	/*
	float x1, x2, x3, x4;
	float y1, y2, y3, y4;
	float z;
	
	x1 = x2 = x-(xsize/2.0f);
	x3 = x4 = x+(xsize/2.0f);
	y1 = y4 = y+(ysize/2.0f);
	y2 = y3 = y-(ysize/2.0f);
	z = 1.0f;
	
	if (focused) {
		glColor3f(1.0f,1.0f,0.0f);
	}
	
	glBegin(GL_QUADS);
	
	glVertex3f(x1, y1, z);
	glVertex3f(x2, y2, z);
	glVertex3f(x3, y3, z);
	glVertex3f(x4, y4, z);
	
	glEnd();
	*/
	if (focused) {
		glColor3f(0.0f,1.0f,0.0f);
	} else {
		glColor3f(1.0f,1.0f,1.0f);
	}
	
	renderText(name,x,y,1.0f,0.015f);
}

int MenuItem::getResponse() {
	return response;
}

void MenuItem::addChild(MenuItem* _item) {
	//std::vector<MenuItem*>::iterator _pos = children.begin();
	children.push_back(_item);
}

std::vector<MenuItem*> MenuItem::getChildren() {
	return children;
}

void MenuItem::setResponse(int r) {
	response = r;
}

/*
void MenuItem::setImage(std::string filename) {
	GLuint texture;
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// texture wraps over edges
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	int width, height;
	void* data;
	FILE* file;
	
	width = 320;
	height = 64;
	
	data = malloc(width*height*3);
	file = fopen(filename, "rb");
	fread(data, width*height*3, 1, file);
	
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	
	
}
*/