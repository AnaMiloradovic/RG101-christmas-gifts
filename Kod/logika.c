#include "funkcije.h"

void resetBlock(int index) {
	gifts[index].x = dropPosition;
	gifts[index].y = 20;
	gifts[index].rotation = 0;
}

void resetSnowman(int index) {
	snowmen[index].x = 0;
	snowmen[index].active = 0;
}

void endGame() {
	//Zavrsavamo igru i ispisujemo rezultat
	if (score>highscore) {
		highscore = score;
	}
	animation_ongoing = 0;
}

void setGame() {
	//Postavljanje prve/nove igre
	srand(time(NULL));
	timer = 0;
	lives = MAX_LIVES;
	score = 0;
	for (int i=0; i<MAX_SNOWMEN; i++){
		resetBlock(i);
		resetSnowman(i);
	}
}

void updateGifts() {
	float dropSpeed = 0.4;
	for (int i=0; i<MAX_GIFTS; i++){
            
		//Ako poklon nije bacen on je na visini 20 i prati poziciju misa
		if (gifts[i].y >= 20) {
			gifts[i].x = dropPosition;
		}
		
		//Ako je bacen onda se spusta brzinom dropSpeed
		//rotation se koristi za animaciju
		else {
			gifts[i].y -= dropSpeed;
			gifts[i].rotation += 0.2;
		}
		//Ako dodirne pod onda se resetuje poklon i igrac gubi zivot
		if (gifts[i].y < 0) {
			resetBlock(i);
			lives--;
			if (lives <= 0) {
				endGame();
			}
		}
	}
}

void updateSnowmen() {
	//Sto je vise vremena proslo od pocetka partije to se snesko belici brze krecu
	double speed = 0.1 + timer*0.00005;

	for (int i=0; i<MAX_SNOWMEN; i++) {
		if (!snowmen[i].active) {
			continue;
		}

		int dir = 1;
		if (snowmen[i].direction) {
			dir = -1;
		}

		//pomeramo sneska levo/desno u zavisnosti od dir/smera
		snowmen[i].x += speed *dir;
                
		//Ako se previse udalji od centra onda igrac gubi zivot i snesko se resetuje
		if (fabs(snowmen[i].x)-playWidth > 0) {
			resetSnowman(i);
			if (snowmen[i].type == 1) { // samo ako je snesko beo igrac gubi zivot
				lives--;
				if (lives <= 0) {
					endGame();
				}
			}
		}
	}
}

void checkHit(){
	//Proverava se sudar sneska i poklona
	for (int i=0; i<MAX_SNOWMEN; i++) {
		if (!snowmen[i].active)
			continue;
                
		//Ako je poklon dovoljno blizu po x i ako je nizi od 4 onda se registruje sudar
		for (int j=0; j<MAX_SNOWMEN; j++) {
			if (fabs(snowmen[i].x-gifts[j].x) < 2 && gifts[j].y < 4) {
				resetBlock(j);
				resetSnowman(i);
				if (snowmen[i].type == 1) { 
					score++; // ako je snesko beo dobijamo poen
				} else {
					score--; // inace ga gubimo
					lives--;
					if (lives <= 0) {
						endGame();
					}
				}
			}
		}
	}
}

void throwGift() {
	//currentGift prati koji poklon sledeci bacamo, kada predje MAX_GIFTS vraca se na 0
	//tako da se redom bacaju pokoni na indeksima 0, 1, 2, 3, 4, 1, 2 itd.
	//Ako je y == 20 to znaci da currentGift nije bacen  tako da moze da se baci
	if (gifts[currentGift].y >= 20) {
		gifts[currentGift].y = 19.9;
		currentGift = (currentGift+1)%MAX_GIFTS;
	}
}

//Brojimo koliko je sneska trenutno aktivno na ekranu
int countSnowmen() {
	int count = 0;
	for(int i=0; i<MAX_SNOWMEN; i++) {
		if(snowmen[i].active)
			count++;
	}
	return count;
}

void addSnowman() {
	//Sansa da snesko bude crn (procenti)
	int darkSnowmanChance = 30;

	//Prolazimo kroz niz i prvog sneska koji nije aktivan aktiviramo
	for (int i=0; i<MAX_SNOWMEN; i++) {
		if (!snowmen[i].active) {
			snowmen[i].active = 1;
			
			//Odredjujemo da li je snesko crn
			
			int r1 = rand() % 100;
			if (r1 < darkSnowmanChance) {
				snowmen[i].type = 2; // crn
			} else {
				snowmen[i].type = 1; // beo
			}

			//Odredjujemo random pravac (levo/desno) i postavljamo poziciju
			//sneska na ivicu ekrana
			int r2 = rand()%2;
			if (r2) {
				snowmen[i].direction = 0;
				snowmen[i].x = -playWidth;
			}
			else {
				snowmen[i].direction = 1;
				snowmen[i].x = playWidth;
			}

			return;
		}
	}
}

void drawText() {
	//Crtamo tekst za zivote, score i highscore
	char str[50];
	glColor3f(1,1,1);
	int len = 0;

	glPushMatrix();
		glRasterPos3f(-13, 18, 2);
		sprintf(str, "Lives: %d", lives);
		len = strlen(str);
		for (int i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
		}
	glPopMatrix();

	glPushMatrix();
		glRasterPos3f(10, 18, 2);
		sprintf(str, "Score: %d", score);
		len = strlen(str);
		for (int i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
		}
	glPopMatrix();

	glPushMatrix();
		glRasterPos3f(10, 17, 2);
		sprintf(str, "Highscore: %d", highscore);
		len = strlen(str);
		for (int i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
		}
	glPopMatrix();
}

void drawEndText() {
	//Crtamo tekst sa instrukcijama za resetovanje igre
	char str[100];
	int len = 0;
	
	char* text1 = "Game over!";
	char* text2 = "Press 'S' to Start";
	char* text3 = "Press 'R' to Restart";
    char* text4 = "Press 'P' to Pause/Unpause or Press 'R' to Restart";

	if (!lives) {
		glColor3f(1, 0, 0);
		glPushMatrix();
			glRasterPos3f(-0.9, 14, 2);
			sprintf(str, "%s", text1);
			len = strlen(str);
			for (int i = 0; i < len; i++) {
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
			}
		glPopMatrix();
	}
	
	
	glColor3f(1, 1, 1);
	glPushMatrix();
		glRasterPos3f(-2.6, 13, 2);
        if(lives== MAX_LIVES && timer == 0)
             sprintf(str, "%s", text2);
        
        else if(!animation_ongoing && lives ){
            glRasterPos3f(-6.0, 13, 2);
            sprintf(str, "%s", text4);
        }
        else{
          glRasterPos3f(-2.6, 13, 2);
		  sprintf(str, "%s", text3);
        }
		len = strlen(str);
		for (int i = 0; i < len; i++) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
                
		}
	glPopMatrix();
}
