#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif




#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <math.h>
#include "Player.h"
#include "Collidable.h"
#include "Ball.h"
#include "drawText.h"
#include "sounds.h"
#include "MenuSystem.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <GL/glut.h>
#endif




using namespace std;

void drawPaddle(float _centrex, float _centrey, float _centrez, float _sizex, float _sizey, float _sizez);
void drawPlayer(Player* player);
void drawBall(Ball* ball);
void detectCollisions();
void resetBall();
void playerScores(Player* _player);
void drawScore();
void pauseGame();
void unpauseGame();
void drawPauseScreen();
void keyOperations();
void executeMenuItem(int);
void updateAIPlayer(Player*);
void newGame();

//void printw(float x, float y, float z, char* format);

Player player1(-2.5f, 0.0f, 0.0f);
Player player2(2.5f, 0.0f, 0.0f);
MenuSystem menuSystem;

Ball ball(0.0f, 0.0f, 0.0f);

bool* keyStates = new bool[256];

bool inPlay = false;
bool paused = false;
bool menuMode = true;
bool musicPlaying = true;
bool aiControl = false;
float logoRotation = 0.0f;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	keyStates[key] = true;
	if (key == 'p') {
		if (paused) {
			unpauseGame();
		} else {
			pauseGame();
		}
	} else if (key == 'm') {
		if (musicPlaying) {
			muteMusic();
			musicPlaying = false;
		} else {
			unmuteMusic();
			musicPlaying = true;
		}
	}
	if (menuMode) {
		if (key == GLUT_KEY_UP) {
			menuSystem.moveUp();
		} else if (key == GLUT_KEY_DOWN) {
			menuSystem.moveDown();
		} else if (key == '\n') {
			executeMenuItem(menuSystem.executeSelected());
		} else if (key == 27) {
			menuSystem.goBack();
		}
	}
}

void handleKeyUp(unsigned char key, int x, int y) {
	keyStates[key] = false;
}

void keyOperations() {
	if (keyStates[(int)'w']) {
		player1.moveUp(0.1f);
	}
	if (keyStates[(int)'s']) {
		player1.moveDown(0.1f);
	}
	if (!keyStates[(int)'w'] && !keyStates[(int)'s']) {
		player1.stop();
	}
	if (!aiControl) {
		if (keyStates[(int)'i']) {
			player2.moveUp(0.1f);
		}
		if (keyStates[(int)'k']) {
			player2.moveDown(0.1f);
		}
		if (!keyStates[(int)'i'] && !keyStates[(int)'k']) {
			player2.stop();
		}
	}
	if (keyStates[27]) {
		inPlay = false;
		if (paused) {
			unpauseGame();
		}
		menuMode = true;
	}
}

void executeMenuItem(int item) {
	if (item == RESPONSE_OPEN_SUBMENU) {
		return;
	} else if (item == RESPONSE_PLAY_2P) {
		aiControl = false;
		inPlay = true;
		menuMode = false;
		newGame();
		return;
	} else if (item == RESPONSE_CONTROLS) {
		menuSystem.showControls();
		return;
	} else if (item == RESPONSE_PLAY_1P) {
		aiControl = true;
		inPlay = true;
		menuMode = false;
		newGame();
		return;
	} else if (item == RESPONSE_QUIT) {
		exit(0);
	}
}

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	//glFrontFace(GL_CW);
	//glEnable(GL_CULL_FACE);
	//glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = 30.0f;
float _cameraAngle = 0.0f;
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;

//Draws the 3D scene
void drawScene() {
	keyOperations();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	
	//glRotatef(-_cameraAngle, 0.0f, 1.0f, 0.0f); //Rotate the camera
	glTranslatef(0.0f, 0.0f, -5.0f); //Move forward 5 units
	
	// add ambient light
	GLfloat ambientColour[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColour);
	
	// add positioned light
	GLfloat lightColour0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat lightPos0[] = { 4.0f, 0.0f, 4.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColour0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	// add directed light
	GLfloat lightColour1[] = { 0.5f, 0.2f, 0.2f, 1.0f };
	GLfloat lightPos1[] = { -1.0f, 0.5f, 0.5f, 0.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColour1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	
	
	glPushMatrix(); //Save the transformations performed thus far
	
	glColor3f(player1.getColour().r, player1.getColour().g, player1.getColour().b);
	drawPlayer(&player1);
	glColor3f(player2.getColour().r, player2.getColour().g, player2.getColour().b);
	drawPlayer(&player2);
	glColor3f(sin((ball.getRotationAmount()*M_PI)/180)*0.9f, 0.0f , 1-sin((ball.getRotationAmount()*M_PI)/180)*0.9f);
	drawBall(&ball);
	
	glColor3f(3.0f, 3.0f, 3.0f);
	
	
	drawScore();
	
	//if (!inPlay) {
	//	//glPushMatrix();
	//	glRotatef(logoRotation, 0.0f, 1.0f, 0.0f);
	//	logoRotation+=5.0f;
	//	drawLogo(-3.0f, 0.8f, 0.2f, 0.3f);
	//	glPopMatrix();
	//	//drawPauseScreen();
	//}
	
	if (paused) {
		drawPauseScreen();
	}
	
	if (menuMode) {
		menuSystem.draw();
	}
	
	glutSwapBuffers();
}

void drawPlayer(Player* _player) {
	drawPaddle(_player->getLocation().x, _player->getLocation().y, _player->getLocation().z, _player->getSize().x, _player->getSize().y, _player->getSize().z);
}

void drawPaddle(float _centrex, float _centrey, float _centrez, float _sizex, float _sizey, float _sizez) {
	float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	
	// coordinates for front face
	x1 = x2 = -(_sizex/2.0f);
	x3 = x4 = _sizex/2.0f;
	y1 = y4 = -(_sizey/2.0f);
	y2 = y3 = _sizey/2.0f;
	z1 = z2 = z3 = z4 = _sizez/2.0f;
	
	glTranslatef(_centrex, _centrey, _centrez);
	//glPushMatrix();
	
	glBegin(GL_QUADS);
	
	// front face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(x1, y1, z1); // top left
	glVertex3f(x2, y2, z2); // bottom left
	glVertex3f(x3, y3, z3); // bottom right
	glVertex3f(x4, y4, z4); // top right
	
	// back face
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(x4, y4, (z4-_sizez)); // top left
	glVertex3f(x3, y3, (z3-_sizez)); // bottom left
	glVertex3f(x2, y2, (z2-_sizez)); // bottom right
	glVertex3f(x1, y1, (z1-_sizez)); // top right
	
	// left face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(x1, y1, (z1-_sizez)); // back top
	glVertex3f(x2, y2, (z2-_sizez)); // back bottom
	glVertex3f(x2, y2, z2); // front bottom
	glVertex3f(x1, y1, z1); // front top
	
	// right face
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x4, y4, z4); // front top
	glVertex3f(x3, y3, z3); // front bottom
	glVertex3f(x3, y3, (z3-_sizez)); // back bottom
	glVertex3f(x4, y4, (z4-_sizez));// back top
	
	// top face
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x1, y1, z1);// front left
	glVertex3f(x1, y1, (z1-_sizez));// back left
	glVertex3f(x4, y4, (z4-_sizez));// back right
	glVertex3f(x4, y4, z4);// front right
	
	// bottom face
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(x3, y3, z3);// front right
	glVertex3f(x3, y3, (z3-_sizez));// back right
	glVertex3f(x2, y2, (z2-_sizez));// back left
	glVertex3f(x2, y2, z2);// front left
	
	
	glEnd();
	
	glPopMatrix();
	glPushMatrix();
	
	//delete &x1, &y1, &z1, &x2, &y2, &z2, &x3, &y3, &z3, &x4, &y4, &z4;
}

void drawBall(Ball* _ball) {
	
	float x1, x2, x3, x4, x5, x6, x7, x8;
	float y1, y2, y3, y4, y5, y6, y7, y8;
	float z1, z2, z3, z4, z5, z6, z7, z8;
	
	x1 = x2 = x5 = x6 = -(_ball->getSize().x/2);
	y1 = y5 = y8 = y4 = _ball->getSize().y/2;
	z1 = z2 = z3 = z4 = _ball->getSize().z/2;
	
	x3 = x4 = x7 = x8 = _ball->getSize().x/2;
	y2 = y3 = y6 = y7 = -(_ball->getSize().y/2);
	z5 = z6 = z7 = z8 = -(_ball->getSize().z/2);
	
	glPushMatrix();
	
	glTranslatef(ball.getLocation().x, ball.getLocation().y, ball.getLocation().z);
	glRotatef(ball.getRotationAmount(), 0.0f, 0.0f, 1.0f);
	
	glBegin(GL_QUADS);
	
	// front face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(x1, y1, z1); // top left
	glVertex3f(x2, y2, z2); // bottom left
	glVertex3f(x3, y3, z3); // bottom right
	glVertex3f(x4, y4, z4); // top right
	
	// back face
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(x8, y8, z8); // top left
	glVertex3f(x7, y7, z7); // bottom left
	glVertex3f(x6, y6, z6); // bottom right
	glVertex3f(x5, y5, z5); // top right (from back view)
	
	// top face
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x4, y4, z4); // top left
	glVertex3f(x8, y8, z8); // bottom left
	glVertex3f(x5, y5, z5); // bottom right
	glVertex3f(x1, y1, z1); // top right
	
	// bottom face
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(x2, y2, z2); // top left
	glVertex3f(x6, y6, z6); // bottom left
	glVertex3f(x7, y7, z7); // bottom right
	glVertex3f(x3, y3, z3); // top right
	
	glEnd();
	
	glPopMatrix();
}

void drawPauseScreen() {
	
	float x1, x2, x3, x4;
	float y1, y2, y3, y4;
	float z;
	
	x1 = x2 = -1.4f;
	x3 = x4 = 1.4f;
	y1 = y4 = 1.4f;
	y2 = y3 = -1.4f;
	
	z = 0.2f;
	
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
	
	width = 512;
	height = 512;
	
	data = malloc(width*height*3);
	file = fopen("pauseTexture.raw", "rb");
	fread(data, width*height*3, 1, file);
	
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	
	glPushMatrix();
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	
	glBegin(GL_QUADS);
	
	glTexCoord2d(0.0,0.0);
	glVertex3f(x1, y1, z);
	
	glTexCoord2f(0.0,1.0);
	glVertex3f(x2, y2, z);
	
	glTexCoord2f(1.0,1.0);
	glVertex3f(x3, y3, z);
	
	glTexCoord2f(1.0,0.0);
	glVertex3f(x4, y4, z);
	
	glEnd();
	
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
	free(data);
	
}

void drawScore() {
	
	int i1 = player1.getScore();
	int i2 = player2.getScore();
	
	drawScoreText(i1, 1);
	drawScoreText(i2, 2);
}

void update(int value) {
	
	if (inPlay) {
		detectCollisions();
		
		if (aiControl) {
			updateAIPlayer(&player2);
		}
		
		player1.updateLocation();
		player2.updateLocation();
		
		ball.updateLocation();
	}
	
	glutPostRedisplay(); //Tell GLUT that the display has changed
	
	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(25, update, 0);
}

void detectCollisions() {
	Rectangle p1Rect = player1.getRectangle();
	Rectangle p2Rect = player2.getRectangle();
	Rectangle ballRect = ball.getRectangle();
	
	// check to see if ball is off screen in Y direction
	if ((ballRect.max.y > 2.0f) || (ballRect.min.y < -2.0f)) {
		ball.inverty();
	}
	
	// check to see if ball has hit a player
	if (ball.getSpeedX() > 0.0f) {
		// ball is going right
		if ((ballRect.max.x > p2Rect.min.x) && (ballRect.max.x < p2Rect.max.x) && (ballRect.min.y < p2Rect.max.y) && (ballRect.max.y > p2Rect.min.y)) {
			// ball has hit player 2
			if (player2.getSpeed() > 0.0f) {
				// player 2 going up
				if (ball.getRotationSpeed() < 0.0f) {
					// ball going clockwise
					player2.applyDamage(ball.getRotationSpeed());
					ball.resetRotation();
					playHitSound();
				} else {
					ball.addAntiClockwiseRotation();
					playSpinSound();
				}
			} else if (player2.getSpeed() < 0.0f) {
				// player 2 going down
				if (ball.getRotationSpeed() > 0.0f) {
					// ball going anticlockwise
					player2.applyDamage(ball.getRotationSpeed());
					ball.resetRotation();
					playHitSound();
				} else {
					ball.addClockwiseRotation();
					playSpinSound();
				}
			} else {
				if (ball.getRotationSpeed() != 0.0f) {
					player2.applyDamage(ball.getRotationSpeed());
					ball.resetRotation();
				}
				playHitSound();
			}
			if (player2.getHealth() > 0) {
				ball.invertx();
			}
		}
	} else {
		// ball is going left
		if ((ballRect.min.x < p1Rect.max.x) && (ballRect.max.x > p1Rect.min.x) && (ballRect.min.y < p1Rect.max.y) && (ballRect.max.y > p1Rect.min.y)) {
			// ball has hit player 1
			if (player1.getSpeed() > 0.0f) {
				// player 1 going up
				if (ball.getRotationSpeed() > 0.0f) {
					// ball going anticlockwise
					player1.applyDamage(ball.getRotationSpeed());
					ball.resetRotation();
					playHitSound();
				} else {
					ball.addClockwiseRotation();
					playSpinSound();
				}
			} else if (player1.getSpeed() < 0.0f) {
				// player 1 going down
				if (ball.getRotationSpeed() < 0.0f) {
					// ball going clockwise
					player1.applyDamage(ball.getRotationSpeed());
					ball.resetRotation();
					playHitSound();
				} else {
					ball.addAntiClockwiseRotation();
					playSpinSound();
				}
			} else {
				if (ball.getRotationSpeed() != 0.0f) {
					player1.applyDamage(ball.getRotationSpeed());
					ball.resetRotation();
				}
				playHitSound();
			}
			if (player1.getHealth() > 0) {
				ball.invertx();
			}
		}
	}
	
	if ((player1.getHealth() <= 0) || (player2.getHealth() <= 0)) {
		playDeadSound();
	}
	
	if (ballRect.min.x > 3.5f) {
		playerScores(&player1);
		ball.setServe(2);
		printf("Player 1 score: %i", player1.getScore());
		resetBall();
	} else if (ballRect.max.x < -3.5f) {
		playerScores(&player2);
		ball.setServe(1);
		printf("Player 2 score: %i", player2.getScore());
		resetBall();
	}
	
}

void playerScores(Player* _player) {
	_player->scorePoints(1);
	playScoreSound();
}

void resetBall() {
	ball.resetPosition();
	player1.resetHealth();
	player2.resetHealth();
}

void newGame() {
	player1.resetScore();
	player2.resetScore();
	player1.resetPosition(-2.5f, 0.0f, 0.0f);
	player2.resetPosition(2.5f,0.0f,0.0f);
	resetBall();
}

void pauseGame() {
	inPlay = false;
	paused = true;
}

void unpauseGame() {
	inPlay = true;
	paused = false;
}

void updateAIPlayer(Player *aiPlayer) {
	if (ball.getLocation().y > aiPlayer->getLocation().y+0.3f) {
		aiPlayer->moveUp(0.05f);
	} else if (ball.getLocation().y < (aiPlayer->getLocation().y-0.3f)) {
		aiPlayer->moveDown(0.05f);
	} else if (ball.getLocation().y == aiPlayer->getLocation().y) {
		aiPlayer->stop();
	}
}

int main(int argc, char** argv) {
	
	// ----------------------------------------------------------------------------
	// This makes relative paths work in C++ in Xcode by changing directory to the Resources folder inside the .app bundle
	#ifdef __APPLE__    
		CFBundleRef mainBundle = CFBundleGetMainBundle();
		CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
		char path[PATH_MAX];
		if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
		{
			// error!
		}
		CFRelease(resourcesURL);
		
		chdir(path);
		std::cout << "Current Path: " << path << std::endl;
	#endif
	
	initOpenAL();
	
	//initialiseSounds();
	
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 640);
	//glutInitWindowSize(1440, 900);
	
	//glutEnterGameMode();
	
	//Create the window
	glutCreateWindow("Spong");
	initRendering();
	
	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutKeyboardUpFunc(handleKeyUp);
	
	glutTimerFunc(25, update, 0); //Add a timer
	
	glutMainLoop();
	return 0;
}