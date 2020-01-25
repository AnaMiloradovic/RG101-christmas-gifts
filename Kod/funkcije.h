#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 30
#define MAX_GIFTS 5
#define MAX_LIVES 5

typedef struct gift{
	float x, y;
	float rotation;
}Gift;

typedef struct snowman{
	double x;
	int direction, active;
	int type; // 1 = beli, 2 = crni
}Snowman;

Gift gifts[MAX_GIFTS];
Snowman snowmen[MAX_GIFTS];

extern void on_keyboard(unsigned char key, int x, int y);
extern void on_timer(int value);
extern void on_mouse_moved(int x, int y);
extern void on_mouse(int button, int state, int x, int y);

extern void drawGifts();
extern void drawSnowman();
extern void drawSnowmen();
extern void setGame();
extern void throwGift();
extern void drawTree();
extern void drawTrees();
extern void drawGround();
extern void resetBlock(int index);
extern void resetSnowman(int index);
extern void endGame();
extern void setGame();
extern void updateGifts();
extern void updateSnowmen();
extern void checkHit();
extern void throwGift();
extern int countSnowmen();
extern void addSnowman();
extern void drawText();
extern void drawEndText();

int animation_ongoing;
int timer;
int width, height;
float dropPosition;

int currentGift;
int playWidth;
int snowmenCount;
int score;
int highscore;
int lives;
