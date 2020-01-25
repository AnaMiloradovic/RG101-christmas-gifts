#include "funkcije.h"

void on_keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 's':
		case 'S':    
			//Pokrece se animacija
			if (!animation_ongoing) {
				setGame();
				animation_ongoing = 1;
				on_timer(TIMER_ID);
			}
			break;
        case 'r':
		case 'R': 
			//Pokrece se animacija
			if (!animation_ongoing) {
				setGame();
				animation_ongoing = 1;
				on_timer(TIMER_ID);
			}
			break;
        case 'p':
        case 'P':
            //animation pause
            if (animation_ongoing == 1)
            {
                animation_ongoing = 0;
                break;
            }
            else
            {
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                animation_ongoing = 1;
                break;
            }
		case 27:
			//Zavrsava se program
			exit(0);
			break;
	}
}

void on_mouse_moved(int x, int y) {
    
	//Pomeramo poziciju poklona na osnovu pozicije misa
	float aspect = (float)width/height;
	dropPosition = x/(float)width;
	dropPosition -= 0.5;
	dropPosition *= aspect;
	dropPosition *= 20;
}


void on_mouse(int button, int state, int x, int y) {
    
	//Kontrolisemo ispustanje poklona na klik ako je igra pocela
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && animation_ongoing) {
		throwGift();
	}
}


