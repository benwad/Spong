/*
 *  drawText.cpp
 *  teapots
 *
 *  Created by Ben Wadsworth on 27/07/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <OpenGL/OpenGL.h>
#include <stdio.h>
#include "drawText.h"


void drawSquare(float xsize, float ysize, float x, float y, float z) {
	float x1, x2, x3, x4;
	float y1, y2, y3, y4;
	
	x1 = x2 = x;
	x3 = x4 = x+xsize;
	y1 = y4 = y;
	y2 = y3 = y-ysize;
	
	glPushMatrix();
	
	glBegin(GL_QUADS);
	
	glVertex3f(x1, y1, z);
	glVertex3f(x2, y2, z);
	glVertex3f(x3, y3, z);
	glVertex3f(x4, y4, z);
	
	glEnd();
	
	glPopMatrix();
}

void drawScoreText(int score, int player) {
	int digits[2];
	digits[0] = (score - score % 10) / 10;
	digits[1] = score % 10;
	
	if (player == 1) {
		if (digits[0] == 0) {
			drawDigit(digits[1], -3.0f, -1.7f, -1.0f, 0.1f);
		} else {
			drawDigit(digits[0], -3.0f, -1.7f, -1.0f, 0.1f);
			drawDigit(digits[1], -2.6f, -1.7f, -1.0f, 0.1f);
		}
	} else if (player == 2) {
		if (digits[0] == 0) {
			drawDigit(digits[1], 3.0f, -1.7f, -1.0f, 0.1f);
		} else {
			drawDigit(digits[0], 2.6f, -1.7f, -1.0f, 0.1f);
			drawDigit(digits[1], 3.0f, -1.7f, -1.0f, 0.1f);
		}
	}
	
}

void drawDigit(int digit, float x, float y, float z, float size) {
	switch(digit) {
		case 0:
			draw0(x, y, z, size);
			return;
		case 1:
			draw1(x, y, z, size);
			return;
		case 2:
			draw2(x, y, z, size);
			return;
		case 3:
			draw3(x,y,z, size);
			return;
		case 4:
			draw4(x,y,z, size);
			return;
		case 5:
			draw5(x,y,z, size);
			return;
		case 6:
			draw6(x,y,z, size);
			return;
		case 7:
			draw7(x,y,z, size);
			return;
		case 8:
			draw8(x,y,z, size);
			return;
		case 9:
			draw9(x,y,z, size);
			return;
	}
}

void draw0(float x, float y, float z, float size) {
	
	float xsize, ysize;
	xsize = ysize = size;
	 
	drawStick(false, x, y, z, 5, xsize); // left stick
	drawStick(false, x+(2*xsize), y, z, 5, xsize); // right stick
	drawSquare(xsize, ysize, x+xsize, y, z); // top square
	drawSquare(xsize, ysize, x+xsize, y-(4*xsize), z); // bottom square
	
}

void draw1(float x, float y, float z, float size) {
	
	float xsize, ysize;
	xsize = ysize = size;	
	
	drawStick(false, x+xsize, y, z, 5, xsize);
}

void draw2(float x, float y, float z, float size) {
	
	float xsize, ysize;
	xsize = ysize = size;
	
	drawStick(true, x, y, z, 2, xsize);
	drawStick(false, x+(2*xsize), y, z, 3, xsize);
	drawStick(true, x, y-(2*ysize), z, 2, xsize);
	drawStick(false, x, y-(3*ysize), z, 2, xsize);
	drawStick(true, x, y-(4*ysize), z, 3, xsize);
	
	
}

void draw3(float x, float y, float z, float size) {
	
	float xsize, ysize;
	xsize = ysize = size;
	
	drawStick(true, x, y, z, 2, xsize);
	drawSquare(xsize, ysize, x+(2*xsize), y-ysize, z);
	drawSquare(xsize, ysize, x+xsize, y-(2*ysize), z);
	drawSquare(xsize, ysize, x+(2*xsize), y-(3*ysize), z);
	drawStick(true, x, y-(4*ysize), z, 2, xsize);
	
}

void draw4(float x, float y, float z, float size) {
	
	float xsize, ysize;
	xsize = ysize = size;
	
	drawStick(false, x, y, z, 4, xsize);
	drawStick(true, x, y-(3*ysize), z, 3, xsize);
	drawStick(false, x+(2*xsize), y-(2*ysize), z, 3, xsize);
}

void draw5(float x, float y, float z, float size) {
	
	float xsize, ysize;
	xsize = ysize = size;
	
	drawStick(true, x, y, z, 3, xsize);
	drawStick(false, x, y, z, 3, xsize);
	drawStick(true, x, y-(2*xsize), z, 2, xsize);
	drawStick(false, x+(2*xsize), y-(2*xsize), z, 2, xsize);
	drawStick(true, x, y-(4*xsize), z, 3, xsize);
	
}

void draw6(float x, float y, float z, float size) {
	
	float xsize, ysize;
	xsize = ysize = size;
	
	drawStick(true, x, y, z, 3, xsize);
	drawStick(false, x, y, z, 5, xsize);
	drawStick(true, x, y-(4*ysize), z, 3, xsize);
	drawStick(true, x, y-(2*ysize), z, 3, xsize);
	drawStick(false, x+(2*xsize), y-(2*ysize), z, 3, xsize);
}

void draw7(float x, float y, float z, float size) {
	
	float xsize, ysize;
	xsize = ysize = size;
	
	drawStick(true, x, y, z, 3, xsize);
	drawStick(false, x+(2*xsize), y, z, 2, xsize);
	drawStick(false, x+xsize, y-(2*ysize), z, 3, xsize);
	
}

void draw8(float x, float y, float z, float size) {
	
	float xsize, ysize;
	xsize = ysize = size;
	
	drawStick(true, x, y, z, 3, xsize);
	drawStick(false, x, y, z, 5, xsize);
	drawStick(true, x, y-(2*ysize), z, 3, xsize);
	drawStick(false, x+(2*xsize), y, z, 5, xsize);
	drawStick(true, x, y-(4*ysize), z, 3, xsize);
	
}

void draw9(float x, float y, float z, float size) {
	
	float xsize, ysize;
	xsize = ysize = size;
	
	drawStick(true, x, y, z, 3, xsize);
	drawStick(false, x, y, z, 3, xsize);
	drawStick(false, x+(2*xsize), y, z, 5, xsize);
	drawStick(true, x, y-(2*ysize), z, 3, xsize);
	drawStick(true, x, y-(4*ysize), z, 2, xsize);
	
}

void drawLetter(char letter, float x, float y, float z, float size) {
	switch (letter) {
		case 'a':
			drawA(x,y,z,size);
			return;
		case 'b':
			drawB(x,y,z,size);
			return;
		case 'c':
			drawC(x,y,z,size);
			return;
		case 'd':
			drawD(x,y,z,size);
			return;
		case 'e':
			drawE(x,y,z,size);
			return;
		case 'f':
			drawF(x,y,z,size);
			return;
		case 'g':
			drawG(x,y,z,size);
			return;
		case 'h':
			drawH(x,y,z,size);
			return;
		case 'i':
			drawI(x,y,z,size);
			return;
		case 'j':
			drawJ(x,y,z,size);
			return;
		case 'k':
			drawK(x,y,z,size);
			return;
		case 'l':
			drawL(x,y,z,size);
			return;
		case 'm':
			drawM(x,y,z,size);
			return;
		case 'n':
			drawN(x,y,z,size);
			return;
		case 'o':
			drawO(x,y,z,size);
			return;
		case 'p':
			drawP(x,y,z,size);
			return;
		case 'q':
			drawQ(x,y,z,size);
			return;
		case 'r':
			drawR(x,y,z,size);
			return;
		case 's':
			drawS(x,y,z,size);
			return;
		case 't':
			drawT(x,y,z,size);
			return;
		case 'u':
			drawU(x,y,z,size);
			return;
		case 'v':
			drawV(x,y,z,size);
			return;
		case 'w':
			drawW(x,y,z,size);
			return;
		case 'x':
			drawX(x,y,z,size);
			return;
		case 'y':
			drawY(x,y,z,size);
			return;
		case 'z':
			drawZ(x,y,z,size);
			return;
		case ' ':
			return;
		case ':':
			drawColon(x,y,z,size);
			return;
		case '0':
			draw0(x,y,z,size);
			return;
		case '1':
			draw1(x,y,z,size);
			return;
		case '2':
			draw2(x,y,z,size);
			return;
		case '3':
			draw3(x,y,z,size);
			return;
		case '4':
			draw4(x,y,z,size);
			return;
		case '5':
			draw5(x,y,z,size);
			return;
		case '6':
			draw6(x,y,z,size);
			return;
		case '7':
			draw7(x,y,z,size);
			return;
		case '8':
			draw8(x,y,z,size);
			return;
		case '9':
			draw9(x,y,z,size);
			return;
		default:
			return;
	}
}

void renderText(std::string text, float x, float y, float z, float size) {
	for (int i=0; i<text.length(); i++) {
		drawLetter(text[i], x+(4*i*size), y, z, size);
	}
}

void drawA(float x, float y, float z, float size) {
	drawStick(true,x,y,z,3,size);
	drawStick(false,x,y,z,5,size);
	drawStick(false,x+(2*size),y,z,5,size);
	drawStick(true,x,y-(2*size),z,3,size);
}

void drawB(float x, float y, float z, float size) {
	drawStick(false,x,y,z,5,size);
	drawStick(true,x,y,z,3,size);
	drawStick(true,x,y-(2*size),z,2,size);
	drawStick(false,x+(2*size),y,z,2,size);
	drawStick(false,x+(2*size),y-(3*size),z,2,size);
	drawStick(true,x,y-(4*size),z,3,size);
}

void drawC(float x, float y, float z, float size) {
	drawStick(true,x,y,z,3,size);
	drawStick(false,x,y,z,5,size);
	drawStick(true,x,y-(4*size),z,3,size);
}

void drawD(float x, float y, float z, float size) {
	drawStick(true,x,y,z,2,size);
	drawStick(false,x,y,z,5,size);
	drawStick(true,x,y-(4*size),z,2,size);
	drawStick(false,x+(2*size),y-size,z,3,size);
}

void drawE(float x, float y, float z, float size) {
	drawStick(false,x,y,z,5,size);
	drawStick(true,x,y,z,3,size);
	drawStick(true,x,y-(2*size),z,3,size);
	drawStick(true,x,y-(4*size),z,3,size);
}

void drawF(float x, float y, float z, float size) {
	drawStick(true,x,y,z,3,size);
	drawStick(false,x,y,z,5,size);
	drawStick(true,x,y-(2*size),z,2,size);
}

void drawG(float x, float y, float z, float size) {
	drawStick(true,x,y,z,3,size);
	drawStick(false,x,y,z,5,size);
	drawStick(true,x,y-(4*size),z,3,size);
	drawStick(false,x+(2*size),y-(2*size),z,3,size);
	drawSquare(size/2.0f, size, x+(1.5f*size), y-(2*size), z);
}

void drawH(float x, float y, float z, float size) {
	drawStick(false,x,y,z,5,size);
	drawStick(false,x+(2*size),y,z,5,size);
	drawStick(true,x,y-(2*size),z,3,size);
}

void drawI(float x, float y, float z, float size) {
	drawStick(false,x+size,y,z,5,size);
}

void drawJ(float x, float y, float z, float size) {
	drawStick(false,x+(2*size),y,z,5,size);
	drawStick(true,x,y-(4*size),z,3,size);
	drawStick(true,x+size,y,z,2,size);
}


void drawK(float x, float y, float z, float size) {
	drawStick(false,x,y,z,5,size);
	drawStick(false,x+(2*size),y,z,2,size);
	drawStick(false,x+(2*size),y-(3*size),z,2,size);
	drawSquare(size,size,x+size,y-(2*size),z);
}

void drawL(float x, float y, float z, float size) {
	drawStick(false,x,y,z,5,size);
	drawStick(true,x,y-(4*size),z,3,size);
}

void drawM(float x, float y, float z, float size) {
	drawStick(false,x,y,z,5,size);
	drawStick(false,x+(2*size),y,z,5,size);
	drawSquare(size/3.0f,size,x+size,y,z);
	drawSquare(size/3.0f,size,x+size+(size/3.0f),y-size,z);
	drawSquare(size/3.0f,size,x+size+2*(size/3.0f),y,z);
}

void drawN(float x, float y, float z, float size) {
	drawStick(false,x,y,z,5,size);
	drawStick(false,x+(2*size),y,z,5,size);
	drawSquare(size/2.0f,size,x+size,y-(1.5f*size),z);
	drawSquare(size/2.0f,size,x+(1.5f*size),y-(2.5f*size),z);
}


void drawO(float x, float y, float z, float size) {
	drawStick(false,x,y,z,5,size);
	drawStick(false,x+(2*size),y,z,5,size);
	drawStick(true,x,y,z,3,size);
	drawStick(true,x,y-(4*size),z,3,size);
}

void drawP(float x, float y, float z, float size) {
	drawStick(true,x,y,z,3,size);
	drawStick(false,x,y,z,5,size);
	drawStick(false,x+(2*size),y,z,3,size);
	drawStick(true,x,y-(2*size),z,3,size);
}

void drawQ(float x, float y, float z, float size) {
	drawStick(true,x,y,z,3,size);
	drawStick(false,x,y,z,5,size);
	drawStick(true,x,y-(4*size),z,3,size);
	drawStick(false,x+(2*size),y,z,5,size);
	drawSquare(size/2.0f,size,x+(size*1.5f),y-(3*size),z);
}

void drawR(float x, float y, float z, float size) {
	drawStick(false,x,y,z,5,size);
	drawStick(true,x,y,z,2,size);
	drawSquare(size,size,x+(2*size),y-size,z);
	drawSquare(size,size,x+size,y-(2*size),z);
	drawStick(false,x+(2*size),y-(3*size),z,2,size);
}

void drawS(float x, float y, float z, float size) {
	drawStick(true,x,y,z,3,size);
	drawStick(false,x,y,z,3,size);
	drawStick(true,x,y-(2*size),z,3,size);
	drawStick(false,x+(2*size),y-(2*size),z,3,size);
	drawStick(true,x,y-(4*size),z,3,size);
}

void drawT(float x, float y, float z, float size) {
	drawStick(true,x,y,z,3,size);
	drawStick(false,x+size,y,z,5,size);
}

void drawU(float x, float y, float z, float size) {
	drawStick(false,x,y,z,5,size);
	drawStick(true,x,y-(4*size),z,3,size);
	drawStick(false,x+(2*size),y,z,5,size);
}

void drawV(float x, float y, float z, float size) {
	drawStick(false,x,y,z,4,size);
	drawStick(false,x+(2*size),y,z,4,size);
	drawSquare(size,size,x+size,y-(4*size),z);
}

void drawW(float x, float y, float z, float size) {
	drawStick(false,x,y,z,5,size);
	drawStick(false,x+(2*size),y,z,5,size);
	drawSquare(size/3.0f,size,x+size,y-(3*size),z);
	drawSquare(size/3.0f,size,x+size+(size/3.0f),y-(2*size),z);
	drawSquare(size/3.0f,size,x+size+2*(size/3.0f),y-(3*size),z);
}

void drawX(float x, float y, float z, float size) {
	drawStick(false,x,y,z,2,size);
	drawStick(false,x+(2*size),y,z,2,size);
	drawStick(false,x,y-(3*size),z,2,size);
	drawStick(false,x+(2*size),y-(3*size),z,2,size);
	drawSquare(size,size,x+size,y-(2*size),z);
}

void drawY(float x, float y, float z, float size) {
	drawStick(false,x+size,y-(2*size),z,3,size);
	drawStick(false,x,y,z,2,size);
	drawStick(false,x+(2*size),y,z,2,size);
}

void drawZ(float x, float y, float z, float size) {
	drawStick(true,x,y,z,3,size);
	drawStick(false,x+(2*size),y,z,3,size);
	drawStick(true,x,y-(2*size),z,3,size);
	drawStick(false,x,y-(2*size),z,3,size);
	drawStick(true,x,y-(4*size),z,3,size);
}

void drawColon(float x, float y, float z, float size) {
	drawSquare(size,size,x+size,y-size,z);
	drawSquare(size,size,x+size,y-(3*size),z);
}

void drawStick(bool horizontal, float x, float y, float z, float length, float thickness) {
	if (horizontal) {
		for (int i=0; i<length; i++) {
			drawSquare(thickness, thickness, x+(i*thickness), y, z);
		}
	} else {
		for (int i=0; i<length; i++) {
			drawSquare(thickness, thickness, x, y-(i*thickness), z);
		}
	}
}

void drawLogo(float cx, float cy, float cz, float thickness) {
	
	
	// draw S
	drawStick(false, cx, cy, cz, 3, thickness);
	drawStick(true, cx, cy, cz, 3, thickness);
	drawStick(true, cx, cy-(2*thickness), cz, 3, thickness);
	drawStick(false, cx+(2*thickness), cy-(2*thickness), cz, 3, thickness);
	drawStick(true, cx, cy-(4*thickness), cz, 3, thickness);
	
	// draw P
	cx += 4*thickness;
	drawStick(false, cx, cy, cz, 5, thickness);
	drawStick(true, cx, cy, cz, 3, thickness);
	drawStick(true, cx, cy-(2*thickness), cz, 3, thickness);
	drawStick(false, cx+(2*thickness), cy, cz, 3, thickness);
	
	// draw O
	cx += 4*thickness;
	drawStick(true, cx, cy, cz, 3, thickness);
	drawStick(true, cx, cy-(4*thickness), cz, 3, thickness);
	drawStick(false, cx, cy, cz, 5, thickness);
	drawStick(false, cx+(2*thickness), cy, cz, 5, thickness);
	
	// draw N
	cx += 4*thickness;
	drawStick(false, cx, cy, cz, 5, thickness);
	drawStick(false, cx+(3*thickness), cy, cz, 5, thickness);
	drawSquare(thickness, thickness, cx+thickness, cy-(1.5f*thickness), cz);
	drawSquare(thickness, thickness, cx+(2*thickness), cy-(2.5f*thickness), cz);
	
	//draw G
	cx += 5*thickness;
	drawStick(false, cx, cy, cz, 5, thickness);
	drawStick(true, cx, cy, cz, 3, thickness);
	drawStick(true, cx, cy-(4*thickness), cz, 3, thickness);
	drawStick(false, cx+(2*thickness), cy-(2*thickness), cz, 3, thickness);
	
}
