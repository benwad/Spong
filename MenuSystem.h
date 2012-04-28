/*
 *  MenuSystem.h
 *  teapots
 *
 *  Created by Ben Wadsworth on 14/08/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

//#include "Menu.h";
#include "MenuItem.h";
#include <string>;
#include <stdlib.h>
#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

class MenuSystem {
	float drawLocX, drawLocY;
	float itemSizeX, itemSizeY;
	std::vector<MenuItem> items;
	MenuItem *selected;
	MenuItem *parent;
	bool controlsShown;
public:
	MenuSystem();
	void addMenuItem(MenuItem);
	void parentChild(MenuItem*,MenuItem*);
	MenuItem* getByName(std::string);
	void listAllItems();
	void listTree(std::string,int);
	void printThisManySpaces(int);
	void drawChildren(MenuItem*,float,float);
	void draw();
	float getLocX();
	float getLocY();
	void moveDown();
	void moveUp();
	void setLocation(float,float);
	void selectItem(MenuItem *);
	void makeParent(MenuItem *);
	void openSubMenu(MenuItem *);
	int executeSelected();
	void goBack();
	void showControls();
	void hideControls();
};

#endif