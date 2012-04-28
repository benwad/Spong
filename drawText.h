/*
 *  drawText.h
 *  teapots
 *
 *  Created by Ben Wadsworth on 27/07/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DRAWTEXT_H
#define DRAWTEXT_H

#include <string>

void drawSquare(float xsize, float ysize, float x, float y, float z);
void drawStick(bool horizontal, float x, float y, float z, float length, float thickness);
void drawScoreText(int score, int player);
void drawDigit(int digit, float x, float y, float z, float size);
void draw0(float x, float y, float z, float size);
void draw1(float x, float y, float z, float size);
void draw2(float x, float y, float z, float size);
void draw3(float x, float y, float z, float size);
void draw4(float x, float y, float z, float size);
void draw5(float x, float y, float z, float size);
void draw6(float x, float y, float z, float size);
void draw7(float x, float y, float z, float size);
void draw8(float x, float y, float z, float size);
void draw9(float x, float y, float z, float size);
void drawLogo(float cx, float cy, float cz, float thickness);
void renderText(std::string text, float x, float y, float z, float size);
void drawLetter(char letter, float x, float y, float z, float size);
void drawA(float x, float y, float z, float size);
void drawB(float x, float y, float z, float size);
void drawC(float x, float y, float z, float size);
void drawD(float x, float y, float z, float size);
void drawE(float x, float y, float z, float size);
void drawF(float x, float y, float z, float size);
void drawG(float x, float y, float z, float size);
void drawH(float x, float y, float z, float size);
void drawI(float x, float y, float z, float size);
void drawJ(float x, float y, float z, float size);
void drawK(float x, float y, float z, float size);
void drawL(float x, float y, float z, float size);
void drawM(float x, float y, float z, float size);
void drawN(float x, float y, float z, float size);
void drawO(float x, float y, float z, float size);
void drawP(float x, float y, float z, float size);
void drawQ(float x, float y, float z, float size);
void drawR(float x, float y, float z, float size);
void drawS(float x, float y, float z, float size);
void drawT(float x, float y, float z, float size);
void drawU(float x, float y, float z, float size);
void drawV(float x, float y, float z, float size);
void drawW(float x, float y, float z, float size);
void drawX(float x, float y, float z, float size);
void drawY(float x, float y, float z, float size);
void drawZ(float x, float y, float z, float size);
void drawColon(float x, float y, float z, float size);
#endif