#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <time.h>
#include "funkcije.h"

void light_init(
	GLfloat* light_ambient,
	GLfloat* light_diffuse,
	GLfloat* light_specular
);

//Deklaracije callback funkcija
static void on_display(void);
static void on_reshape(int w, int h);

int main(int argc, char **argv) {
    
    //Inicijalizuje se GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	// Kreira se prozor
	glutInitWindowSize(1280, 830);
	glutInitWindowPosition(200, 200);
    glutCreateWindow("Christmas Gifts");

	//Registruju se funkcije za obradu dogadjaja
	glutKeyboardFunc(on_keyboard);
	glutReshapeFunc(on_reshape);
	glutPassiveMotionFunc(on_mouse_moved);
	glutMouseFunc(on_mouse);
	glutDisplayFunc(on_display);

  	//Na pocetku je animacija neaktivna
	//Obavlja se OpenGL inicijalizacija
	
	//Postavljamo osnovnu boju na boju neba
    glClearColor(0.05, 0.08, 0.28, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	animation_ongoing = 0;
	dropPosition = 0;
	currentGift = 0;
	playWidth = 23;
	snowmenCount = 0;
	score = 0;
	highscore = 0;
	lives = MAX_LIVES;
	
	setGame();
	glutMainLoop();

	return 0;
}

void light_on() {
    
	GLfloat light_ambient[] =  {0.5, 0.5, 0.5, 1};
	GLfloat light_diffuse[] =  {0.9, 0.9, 0.9, 1};
	GLfloat light_specular[] = {1.0, 1.0, 1.0, 1};
	light_init(light_ambient, light_diffuse, light_specular);
}

void light_off() {
    
	GLfloat light_ambient[] =  {0.1, 0.1, 0.1, 1};
	GLfloat light_diffuse[] =  {0.1, 0.1, 0.1, 1};
	GLfloat light_specular[] = {0.0, 0.0, 0.0, 1};
	light_init(light_ambient, light_diffuse, light_specular);
}

void light_init(
        GLfloat* light_ambient,
        GLfloat* light_diffuse,
        GLfloat* light_specular
	) {
	GLfloat light_position[] = {10.0, 5.0, 0.0, 0};
	
	// ukljucuje se osvjetljenje
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void on_timer(int value) {
    if (value != TIMER_ID) {
    	return;
    }

	//Na svakih 600 frame-ova se povecava broj sneska koji se pojavljuju
	//Dok ne stignemo do 600tog frame-a, imamo 2 sneska
	snowmenCount = timer/600 + 2;
	int currentSnowmenCount = countSnowmen();

	//Ako je trenutno aktivno manje nego sto treba dodajemmo sneska
	if (currentSnowmenCount < snowmenCount) {
		addSnowman();
	}

	updateGifts();
	updateSnowmen();
	checkHit();

	timer++;
        
	//Forsira se ponovno iscrtavanje prozora
	glutPostRedisplay();
        
        //Po potrebi se ponovo postavlja tajmer
        if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}

static void on_reshape(int w, int h) {
    //Pamte se sirina i visina prozora
    width = w;
    height = h;

    //Podesava se viewport
    glViewport(0, 0, width, height);

    //Podesava se projekcija
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 50);
}

static void on_display(void) {
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 10, 20,
			  0, 10,  0,
			  0,  1,  0);

	//'Gasimo svetla' ako igra nije aktivna trenutno
	if (animation_ongoing) {
		light_on();
	} else {
		light_off();
	}
	
/*	glEnable(GL_TEXTURE_2D);*/
	
	//Iskljucujemo osvetljenje za 2D objekte
	glDisable(GL_LIGHTING);
		drawText();
		drawGifts();
		if (!animation_ongoing) {
			drawEndText();
		}
	glEnable(GL_LIGHTING);

	//I nakon paljenja iscrtavamo 3D
	drawGround();
	drawTrees();
	drawSnowmen();
    
	glutSwapBuffers();
}
