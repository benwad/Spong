/*
 *  Menu.cpp
 *  teapots
 *
 *  Created by Ben Wadsworth on 14/08/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Menu.h"

Menu::Menu(std::string _name) {
	name = _name;
}

Menu::~Menu() {
	items.~vector<MenuItem*>();
}

void Menu::addItemAt(int _pos, MenuItem *_item) {
	items.at(_pos) = _item;
}

MenuItem* Menu::getItemAt(int _pos) {
	return items.at(_pos);
}