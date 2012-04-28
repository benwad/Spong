/*
 *  MenuSystem.cpp
 *  teapots
 *
 *  Created by Ben Wadsworth on 14/08/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "MenuSystem.h"

MenuSystem::MenuSystem() {
	itemSizeX = 0.8f;
	itemSizeY = 0.1f;
	
	drawLocX = -0.8f;
	drawLocY = -0.1f;
	
	addMenuItem(MenuItem("root"));
	addMenuItem(MenuItem("play"));
	addMenuItem(MenuItem("controls"));
	addMenuItem(MenuItem("quit"));
	addMenuItem(MenuItem("single player"));
	addMenuItem(MenuItem("multiplayer"));
	
	getByName("root")->setResponse(RESPONSE_OPEN_SUBMENU);
	parentChild(getByName("root"), getByName("play"));
	parentChild(getByName("root"), getByName("controls"));
	parentChild(getByName("root"), getByName("quit"));
	
	getByName("play")->setResponse(RESPONSE_OPEN_SUBMENU);
	parentChild(getByName("play"), getByName("single player"));
	parentChild(getByName("play"), getByName("multiplayer"));
	
	//getByName("options")->setResponse(RESPONSE_OPEN_SUBMENU);
	//parentChild(getByName("options"), getByName("sound"));
	//parentChild(getByName("options"), getByName("other"));
	
	getByName("single player")->setResponse(RESPONSE_PLAY_1P);
	getByName("multiplayer")->setResponse(RESPONSE_PLAY_2P);
	getByName("controls")->setResponse(RESPONSE_CONTROLS);
	getByName("quit")->setResponse(RESPONSE_QUIT);
	
	makeParent(getByName("root"));
	selectItem(getByName("play"));
	listTree("root", 0);
}

void MenuSystem::selectItem(MenuItem *item) {
	item->setFocused(true);
	if (selected != NULL) {
		selected->setFocused(false);
	}
	selected = item;
}

void MenuSystem::makeParent(MenuItem *item) {
	parent = item;
}

void MenuSystem::drawChildren(MenuItem* menu, float ox, float oy) {
	std::vector<MenuItem*> myChildren = menu->getChildren();
	float dy = itemSizeY+0.05f;
	
	int i=0;
	std::vector<MenuItem*>::iterator it;
	for (it = myChildren.begin(); it != myChildren.end(); it++) {
		(*it)->drawAt(ox, oy-(i*dy));
		i++;
	}
}

void MenuSystem::draw() {
	float x = drawLocX;
	float y = drawLocY;
	drawChildren(getByName("root"), x, y);
	if (parent != getByName("root")) {
		drawChildren(parent,x+itemSizeX+0.05f,y);
	}
	//selected = *(getByName("root")->getChildren()).begin();
	if (selected->getResponse() == RESPONSE_OPEN_SUBMENU) {
		drawChildren(selected, x+itemSizeX+0.05f, y);
	}
	glColor3f(1.0f,1.0f,1.0f);
	renderText("music: farmer in the sky : jahtari riddim force", -0.9f, -1.5f, 1.0f, 0.01f);
	renderText("spong", -1.0f, 1.5f, 1.0f, 0.1f);
	
	if (controlsShown) {
		renderText("w : player 1 up", getLocX()+1.1f, getLocY()+0.1f, 1.0f, 0.015f);
		renderText("s : player 1 down", getLocX()+1.1f, getLocY(), 1.0f, 0.015f);
		renderText("i : player 2 up", getLocX()+1.1f, getLocY()-0.1f, 1.0f, 0.015f);
		renderText("k : player 2 down", getLocX()+1.1f, getLocY()-0.2f, 1.0f, 0.015f);
		renderText("p : pause", getLocX()+1.1f, getLocY()-0.3f, 1.0f, 0.015f);
		renderText("m : music on or off", getLocX()+1.1f, getLocY()-0.4f, 1.0f, 0.015f);
		renderText("esc : main menu", getLocX()+1.1f, getLocY()-0.5f, 1.0f, 0.015f);
		if (selected != getByName("controls")) {
			hideControls();
		}
	}
}

MenuItem* MenuSystem::getByName(std::string _name) {
	std::vector<MenuItem>::iterator it;
	for (it = items.begin(); it != items.end(); it++) {
		if (it->getName() == _name) {
			return (MenuItem*)&*it;
		}
	}
	return (MenuItem*)NULL;
}

void MenuSystem::listAllItems() {
	std::vector<MenuItem>::iterator it;
	for (it = items.begin(); it != items.end(); it++) {
		cout << it->getName() << '\n';
	}
}

void MenuSystem::listTree(std::string rootName, int level) {
	MenuItem *root = getByName(rootName);
	std::vector<MenuItem*>myChildren = root->getChildren();
	std::vector<MenuItem*>::iterator childIterator;
	for (childIterator = myChildren.begin();
		 childIterator != myChildren.end();
		 childIterator++) {
		printThisManySpaces(level);
		cout << (*childIterator)->getName() << '\n';
		if ((*childIterator)->getResponse() == RESPONSE_OPEN_SUBMENU) {
			listTree((*childIterator)->getName(), level+1);
		}
	}
}

void MenuSystem::printThisManySpaces(int num) {
	for (int i=0; i<num; i++) {
		cout << " ";
	}
}

void MenuSystem::addMenuItem(MenuItem item) {
	items.push_back(item);
}

void MenuSystem::parentChild(MenuItem* parent, MenuItem* child) {
	parent->addChild(child);
}

float MenuSystem::getLocX() {
	return drawLocX;
}

float MenuSystem::getLocY() {
	return drawLocY;
}

void MenuSystem::setLocation(float x, float y) {
	drawLocX = x;
	drawLocY = y;
}

void MenuSystem::moveDown() {
	
	std::vector<MenuItem*>::iterator it;
	std::vector<MenuItem*>currentMenu = parent->getChildren();
	for (it = currentMenu.begin(); it != currentMenu.end(); it++) {
		if ((*it)->getName() == selected->getName()) {
			if (it != currentMenu.end()-1) {
				selectItem(selected+1);
				drawLocY += itemSizeY+0.05f;
			}
			return;
		}
	}
	
}

void MenuSystem::moveUp() {
	
	std::vector<MenuItem*>::iterator it;
	std::vector<MenuItem*>currentMenu = parent->getChildren();
	for (it = currentMenu.begin(); it != currentMenu.end(); it++) {
		if ((*it)->getName() == selected->getName()) {
			if (it != currentMenu.begin()) {
				selectItem(selected-1);
				drawLocY -= itemSizeY+0.05f;
			}
			return;
		}
	}
}

int MenuSystem::executeSelected() {
	if (selected->getResponse() == RESPONSE_OPEN_SUBMENU) {
		openSubMenu(selected);
		return RESPONSE_OPEN_SUBMENU;
	} else {
		return selected->getResponse();
	}
}

void MenuSystem::showControls() {
	controlsShown = true;
}

void MenuSystem::hideControls() {
	controlsShown = false;
}

void MenuSystem::goBack() {
	if (parent != getByName("root")) {
		selectItem(parent);
		makeParent(getByName("root"));
		drawLocX += itemSizeX + 0.05f;
	}
	if (controlsShown) {
		hideControls();
	}
	
}

void MenuSystem::openSubMenu(MenuItem *menu) {
	drawLocX -= itemSizeX + 0.05f;
	std::vector<MenuItem*> newMenu = menu->getChildren();
	makeParent(selected);
	selectItem(*(newMenu.begin()));
}

/*
void MenuSystem::addMenu(Menu menu, std::vector<Menu*>::iterator _pos) {
	menus.insert(_pos, 1, &menu);
}
*/

/*
void addItemToMenu(MenuItem *item, Menu *menu) {
}
*/