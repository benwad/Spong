/*
 *  Menu.h
 *  teapots
 *
 *  Created by Ben Wadsworth on 14/08/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MENU_H
#define MENU_H

#include "MenuItem.h"
#include <string>
#include <vector>

class Menu {
protected:
	std::string name;
	std::vector<MenuItem*> items;
	MenuItem *selectedItem;
	int numItems;
	float locx, locy;
public:
	Menu(std::string);
	~Menu();
	void addItemAt(int, MenuItem *);
	MenuItem* getItemAt(int);
	void drawAt(float,float);
};

#endif