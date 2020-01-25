#include "funkcije.h"

void drawGifts(){
	//Prolazimo kroz sve poklone i crtamo ih
	for (int i=0; i<MAX_GIFTS; i++) {
		glPushMatrix();
		glColor3f(0.68, 0, 0);
		glTranslatef(gifts[i].x, gifts[i].y, 0);
                
		//Animacija rotiranja - rotation se povecava dok poklon pada
		if (gifts[i].rotation > 0) {
			glRotatef(gifts[i].rotation*10, 1, 0, 0);
			glRotatef(gifts[i].rotation*25, 0, 1, i*0.2);
		}
		glScalef(1.5, 1, 1.2);
		glutSolidCube(1);

		//Ukras
		glColor3f(0, 0.2, 0.11);
		glPushMatrix();
		glScalef(0.2, 1.1, 1.1);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glScalef(1.1, 1.1, 0.2);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glScalef(1, 1, 0.3);
		glTranslatef(-0.2, 0.8, 0);
		glutSolidSphere(0.3, 10, 10);
		glTranslatef(0.4, 0, 0);
		glutSolidSphere(0.3, 10, 10);
		glPopMatrix();

		glPopMatrix();
	}
}

void drawSnowman(int type) {
	// Iscrtavanje jednog sneska, namestamo boju i materijal
	GLfloat ambient_snowman_white[]  = {1.0, 0.98, 0.98, 1.0};
	GLfloat diffuse_snowman_white[]  = {1.0, 0.98, 0.98, 1.0};
	GLfloat specular_snowman_white[] = {1.0, 0.98, 0.98, 1.0};
	
	GLfloat ambient_snowman_black[]  = {0.1, 0.1, 0.1, 1.0};
	GLfloat diffuse_snowman_black[]  = {0.1, 0.1, 0.1, 1.0};
	GLfloat specular_snowman_black[] = {0.1, 0.1, 0.1, 1.0};
	
	GLfloat shininess_snowman  = 5;
	
	if (type == 1) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_snowman_white);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_snowman_white);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_snowman_white);
	} else {
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_snowman_black);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_snowman_black);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_snowman_black);
	}
	glMaterialf(GL_FRONT, GL_SHININESS, shininess_snowman);
	
	
	//Animiramo sneska pomocu 'timer' promenljive
	int hopInterval = 20;
	float bounce = 0;
	int hopValue = timer%hopInterval;
	
	if (hopValue >= 0 && hopValue < hopInterval/2) {
		bounce += hopValue;
	}
	if (hopValue >= hopInterval/2 && hopValue < hopInterval) {
		bounce = hopInterval - hopValue;
	}
	
	glPushMatrix();
		glutSolidSphere(0.8, 20, 20);
		glTranslatef(0, 0.8 + bounce/30, 0);
		glutSolidSphere(0.6, 20, 20);
		glTranslatef(0, 0.6 + bounce/30, 0);
		glutSolidSphere(0.5, 20, 20);
		
		glRotatef(90, 0, 1, 0);
		
		//Materijali nosa
		GLfloat ambient_nose[]  = {1.0, 0.5, 0.31, 1.0};
		GLfloat diffuse_nose[]  = {1.0, 0.5, 0.31, 1.0};
		GLfloat specular_nose[] = {1.0, 0.5, 0.31, 1.0};
		GLfloat shininess_nose = 5;
	
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_nose);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_nose);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_nose);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess_nose);
		
		glutSolidCone(0.1, 1, 20, 20);
	glPopMatrix();
}

void drawSnowmen() {
	//Crtamo svakog sneska koji je aktivan
	for (int i=0; i<MAX_SNOWMEN; i++) {
		if (!snowmen[i].active) {
			continue;
		}
			
		glPushMatrix();
			//Stavlja ih na malo razlicite y da se ne bi preklopili
			glTranslatef(snowmen[i].x, 1+i*0.2, 0);
			glScalef(1.5, 1.5, 1.5);
		            
			//Okrecemo sneska ako se krece u suprotnoj strani u odnosu na sliku
			if (snowmen[i].direction) {
				glScalef(-1, 1, 1);
			}
		
			//glNormal3f(0, 0, -1);
			drawSnowman(snowmen[i].type);
		glPopMatrix();
	}
}

void drawTree() {
	//Iscrtavamo 3D drvo od 3 konusa
	GLfloat ambient[] = {0.03, 0.37, 0.15, 1};
	GLfloat diffuse[] = {0.0, 0.3, 0.0, 1};
	GLfloat specular[] = {0.0, 0.3, 0.0, 1};
	GLfloat shininess = 5;
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	
	glPushMatrix();
		glRotatef(-90.0, 1, 0, 0);
		glutSolidCone(2.5, 3.5, 20, 20);
		glTranslatef(0, 0, 2);
		glutSolidCone(2.0, 3.0, 20, 20);
		glTranslatef(0, 0, 1.5);
		glutSolidCone(1.5, 2.5, 20, 20);
	glPopMatrix();
}

void drawTrees(){
    
	//Podesavamo gustinu pozadine izborom kolicine drveca
	int trees = 15;
	int treeRows = 6;
	for (int i=0; i<treeRows; i++) {
		for (int j=0; j<trees; j++){
			glPushMatrix();
				glTranslatef(-30+j*6+i*3, 3, -3-3*i);
				drawTree();
			glPopMatrix();
		}
	}
}

void drawGround() {
	//Iscrtavamo zemlju
	GLfloat ambient_ground[] = {0.5, 0.5, 0.5, 1};
	GLfloat diffuse_ground[] = {0.4, 0.4, 0.4, 1};
	GLfloat specular_ground[] = {0.6, 0.6, 0.6, 1};
	GLfloat shininess_ground = 5;
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_ground);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_ground);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_ground);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess_ground);
	
	glPushMatrix();
		glTranslatef(0, -1, 0);
		glScalef(100, 0, 40);
		glutSolidCube(1);
	glPopMatrix();
}






