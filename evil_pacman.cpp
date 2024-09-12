#include <random>
#include <stdio.h>
#include <glut.h>
#include <string.h>
#include <SDL.h>
#include <SDL_mixer.h>
# define M_PI           3.14159265358979323846 

int backRef = 10;
int first = 1;
int scaleUp = 1;
int damaged = 0;
int posX = 300;
int posY = 230;
int rot = -120;
int score = 0;
int timeCurr = 40;
int health = 5;
int gameOver = 0;
int won = 0;
int rotAnim = 10;
int translateOne = 0;
int translateTwo = -700;
int SecondsPlayed = 0;
double ScaleAnim = 1;
int changeDirec = 0;
int direc = 1;
int changeVal = 1000;
std::random_device rd;
std::mt19937 generator(rd());
std::uniform_int_distribution<int> distributionX(20, 610);
std::uniform_int_distribution<int> distributionY(20, 410);
std::uniform_int_distribution<int> distributionXStars(0, 700);
std::uniform_int_distribution<int> distributionYStars(0, 500);
int genXCollect[8];
int genYCollect[8];
int genXObstacle[4] = { 200, 200, 500, 500 };
int genYObstacle[4] = { 400 , 120 , 400 , 120 };
int genXStars[100];
int genYStars[100];
float red = 0;
float blue = 0;
float green = 0;
int staredEffect = 0;
int staredTime = 0;
int PlayNow = 1;
Mix_Chunk* bruh = NULL;
Mix_Chunk* coin = NULL;
Mix_Chunk* powerUp = NULL;
Mix_Music* loseMusic = NULL;
Mix_Music* winMusic = NULL;


//sf::Music music;



float getRandomFloat() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<float> dis(0.5f, 1.0f);
	return dis(gen);
}

void appendString(char* dest, const char* src) {
	while (*dest) {
		++dest;
	}
	while (*src) {
		*dest++ = *src++;
	}
	*dest = '\0';
}

void setTime(int a) {
	timeCurr--;
	if (staredTime != 0)
		staredTime--;
	if (staredTime == 0)
		staredEffect = 0;
	glutPostRedisplay();
	glutTimerFunc(1000, setTime, 1);

}


void output(int x, int y, float r, float g, float b, void* font, char* string)
{
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	int len, i;
	len = (int)strlen(string);

	glPushMatrix();
	glScalef(20.0f, 20.0f, 1.0f);

	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}

	glPopMatrix();
}

int touchObs() {
	if (posX >= 121 && posX <= 195 && posY <= 120)
		return 1;
	if (posX >= 121 && posX <= 195 && posY >= 322)
		return 1;
	if (posX >= 425 && posX <= 495 && posY <= 120)
		return 1;
	if (posX >= 425 && posX <= 495 && posY >= 325)
		return 1;

	return 0;
}
//posX >= 210 && posX <= 400 && posY >= 170 && posY <= 250 ||

void key(unsigned char k, int x, int y)
{

	if (k == 'w') {
		posY += 15;
		rot = -30;
	}
	if (k == 'a') {
		posX -= 15;
		rot = 60;
	}
	if (k == 's') {
		posY -= 15;
		rot = -210;
	}
	if (k == 'd') {
		posX += 15;
		rot = -120;
	}
	if (posX > 590) {
		posX = 590;
		if (!staredEffect) {
			health--;
			Mix_PlayChannel(-1, bruh, 0);
		}
	}
	if (posY > 400) {
		posY = 390;
		if (!staredEffect) {
			health--;
			Mix_PlayChannel(-1, bruh, 0);
		}
	}
	if (posX < 40) {
		posX = 30;
		if (!first && !staredEffect) {
			health--;
			Mix_PlayChannel(-1, bruh, 0);
		}
	}
	if (posY < 30) {
		posY = 30;
		if (!first && !staredEffect) {
			Mix_PlayChannel(-1, bruh, 0);
			health--;
		}
	}
	if (touchObs()) {
		if (!staredEffect) {
			switch (k) {
			case 'd':
				posX -= 15;
				break;
			case 's':
				posY += 15;
				break;
			case 'a':
				posX += 15;
				break;
			case 'w':
				posY -= 15;
				break;
			default:
				break;
			}
			health--;
			Mix_PlayChannel(-1, bruh, 0);
		}
	}
	//printf(" posX: %d posY: %d", posX, posY);
	first = 0;
	glutPostRedisplay();
}




void Display() {
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glTranslated(translateOne, 0, 0);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0, 0);
	glVertex2f(0, 500);
	glVertex2f(700, 500);
	glVertex2f(700, 0);
	glEnd();
	for (int i = 0; i < 100;i++) {
		glBegin(GL_LINES);
		glColor3f(1.0, 1.0f, 1.0f);
		glVertex2f(genXStars[i], genYStars[i]);
		glVertex2f(genXStars[i] - 20, genYStars[i]);
		glEnd();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(translateTwo, 0, 0);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0, 0);
	glVertex2f(0, 500);
	glVertex2f(700, 500);
	glVertex2f(700, 0);
	glEnd();
	for (int i = 0; i < 100;i++) {
		glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(genXStars[i], genYStars[i]);
		glVertex2f(genXStars[i] - 20, genYStars[i]);
		glEnd();
	}
	glPopMatrix();
	glLineWidth(1);

	if (gameOver) {
		if (!PlayNow)
			SecondsPlayed++;
		if (SecondsPlayed > 930 && !won)
			Mix_FadeOutMusic(1200);
		char numCStr[20];
		sprintf(numCStr, "%d", score);
		char use[100] = "Score: ";
		appendString(use, numCStr);
		glPushMatrix();
		output(300, 420, 1, 1, 1, GLUT_BITMAP_TIMES_ROMAN_24, "Game Over");
		if (won) {
			if (PlayNow) {
				Mix_HaltMusic();
				Mix_FadeInMusic(winMusic, 0,10000);
				PlayNow = 0;
				backRef = 35;
			}
			output(310, 390, 1, 1, 1, GLUT_BITMAP_TIMES_ROMAN_24, "You Won");
		}
		else {
			if (PlayNow) {
				Mix_HaltMusic();
				Mix_PlayMusic(loseMusic, -1);
				PlayNow = 0;
			}
			
			output(310, 390, 1, 1, 1, GLUT_BITMAP_TIMES_ROMAN_24, "You Lost");
		}
		output(320, 360, 1, 1, 1, GLUT_BITMAP_TIMES_ROMAN_24, use);
		glPopMatrix();
		glFlush();
		return;
	}

	if (score >= 2) {
		glPushMatrix();
		glTranslated(615, 415, 0);
		glRotated(rotAnim, 0, 0, 1);
		glTranslated(-615, -415, 0);
		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.5f);
		glVertex2f(600, 400);
		glVertex2f(600, 430);
		glVertex2f(630, 430);
		glVertex2f(630, 400);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(600, 400);
		glVertex2f(630, 430);
		glVertex2f(630, 400);
		glVertex2f(600, 430);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(600, 415);
		glVertex2f(630, 415);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(615, 400);
		glVertex2f(615, 430);
		glEnd();
		glPointSize(6.5f);
		glBegin(GL_POINTS);
		glVertex2f(615, 415);
		glColor3f(0.5f, 0.5f, 0.0f);
		glEnd();
		glPopMatrix();
	}




	glPushMatrix();
	char numCStr[20];
	char num2[20];
	sprintf(numCStr, "%d", score);
	sprintf(num2, "%d", timeCurr);

	char use[100] = "Score: ";
	char use2[100] = "Time: ";
	appendString(use, numCStr);
	appendString(use2, num2);
	output(310, 470, 1, 1, 1, GLUT_BITMAP_TIMES_ROMAN_24, use);
	output(550, 470, 1, 1, 1, GLUT_BITMAP_TIMES_ROMAN_24, use2);
	glPopMatrix();

	glPushMatrix();
	for (int i = 0; i < health; i++) {
		glPointSize(20);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(40 + (21 * i), 478.0f);
		glEnd();
	}
	glPopMatrix();


	for (int i = 0; i < 8; i++) {
		int generatedX = genXCollect[i];
		int generatedY = genYCollect[i];
		if (genXCollect[i] == NULL)
			continue;
		if (i > 3) {
			const float radius = 15.0f;
			glPushMatrix();
			glTranslated(generatedX, generatedY, 0);
			glScaled(ScaleAnim, ScaleAnim, 0);
			glRotated(rotAnim, 0, 0, 1);
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(1.0f, 0.84f, 0.0f);


			glVertex2f(0.0f, 0.0f);


			int numSegments = 8;

			for (int i = 0; i <= numSegments; ++i) {
				float theta = 2.0f * 3.14159f * static_cast<float>(i) / static_cast<float>(numSegments);
				float x = radius * cos(theta);
				float y = radius * sin(theta);
				glVertex2f(x, y);
			}
			glEnd();


			const float lineLength = 14.0f;
			const float lineWidth = 4.0f;
			glLineWidth(lineWidth);
			glColor3f(0.0f, 0.0f, 0.0f);

			glBegin(GL_LINES);
			glVertex2f(0.0f, lineLength / 2.0f);
			glVertex2f(0.0f, -lineLength / 2.0f);
			glEnd();
			glBegin(GL_LINES);
			glVertex2f(0.0f, lineLength / 2.0f);
			glVertex2f(-6.0f, (-lineLength / 2.0f) / 9);
			glEnd();
			glBegin(GL_LINES);
			glVertex2f(-6.0f, (-lineLength / 2.0f));
			glVertex2f(6.0f, (-lineLength / 2.0f));
			glEnd();

			glPopMatrix();
			glLineWidth(1.0f);
			continue;
		}
		if (i % 2 != 0) {
			glPushMatrix();
			glTranslatef(generatedX, generatedY, 0);
			glScalef(ScaleAnim, ScaleAnim, 0);
			glRotated(-16, 0, 0, 1);
			float radius = 15;
			float angle = 0.0;
			int numPoints = 10;
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(red, green, blue);
			glVertex2f(0.0, 0.0);
			for (int i = 0; i <= numPoints; i++) {
				float x = radius * cos(angle);
				float y = radius * sin(angle);
				if (i % 2 == 0) {
					x *= 0.5;
					y *= 0.5;
				}
				glVertex2f(x, y);
				angle += 2 * M_PI / numPoints;
			}
			glEnd();
			glPointSize(7.0f);
			glBegin(GL_POINTS);
			glVertex2f(-4.69, 15);
			glEnd();
			glBegin(GL_POINTS);
			glVertex2f(-4.69, -15);
			glEnd();
			glBegin(GL_POINTS);
			glVertex2f(12.69, -10);
			glEnd();
			glPopMatrix();
			continue;
		}
		glPushMatrix();
		glTranslatef(generatedX, generatedY, 0);
		glScalef(ScaleAnim, ScaleAnim, 0);
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(-12.5, -12.5);
		glVertex2f(-12.5 + 25, -12.5);
		glVertex2f(-12.5, -12.5 + 25);
		glVertex2f(-12.5 + 25, -12.5 + 25);
		glVertex2f(-12.5, -12.5);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f((-12.5 + 25) / 128, -12.5 + 25);
		glVertex2f((-12.5 + 25) / 128, -12.5);
		glEnd();
		glPointSize(6.3f);
		glBegin(GL_POINTS);
		glVertex2f(0.0f, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(-12.5, 12.5 / 128);
		glVertex2f(-12.5 + 25, 12.5 / 128);
		glEnd();
		glPopMatrix();
	}

	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(40, 460);
	glVertex2f(660, 460);
	glVertex2f(660, 40);
	glVertex2f(40, 40);
	glVertex2f(40, 460);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2f(40 - 5, 460 + 5);
	glVertex2f(660 + 5, 460 + 5);
	glVertex2f(660 + 5, 40 - 5);
	glVertex2f(40 - 5, 40 - 5);
	glVertex2f(40 - 5, 460 + 5);
	glEnd();
	glPopMatrix();

	for (int i = 0; i < 4; i++) {
		int generatedX = genXObstacle[i];
		int generatedY = genYObstacle[i];
		glPushMatrix();
		glTranslatef(generatedX, generatedY, 0);
		glScalef(2, 2, 0);
		glBegin(GL_POLYGON);
		glColor3f(0.6, 0.4, 0.2);
		glVertex2f(-10, -6);
		glVertex2f(0, -12);
		glVertex2f(10, -6);
		glVertex2f(6, 10);
		glVertex2f(-6, 10);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(-10, -6);
		glVertex2f(9, 12);
		glVertex2f(10, -6);
		glVertex2f(-8, 12);
		glEnd();
		glPopMatrix();
	}



	glPushMatrix();
	int minX = (-3 * 10) + posX + 40;
	int maxX = (3.5 * 10) + posX + 40;
	int minY = (-2.5 * 10) + posY + 40;
	int maxY = (3 * 10) + posY + 40;
	int centerX = posX + 40;
	int centerY = posY + 40;
	//printf("%dminX %dmaxX %dminY %dmaxY ", minX, maxX, minY, maxY);
	glColor3f(1.0f, 1.0f, 0.0f);
	if (staredEffect)
		glColor3f(red, green, blue);
	glTranslated(posX, posY, 0);
	glTranslated(40, 40, 0);
	glScaled(10, 10, 0);
	glRotated(rot, 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 3.0);
	glVertex2f(2.0, 3.0);
	glVertex2f(3.0, 2.0);
	glVertex2f(3.50, .50);
	glVertex2f(3.0, -1.0);
	glVertex2f(2.0, -2.0);
	glVertex2f(0.0, -2.50);
	glVertex2f(-2.0, -2.0);
	glVertex2f(-3.0, -1.0);
	glVertex2f(-3, 0);
	glVertex2f(-3, 1.5);
	glEnd();
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor3f(0.6f, 0.0f, 0.0f);
	glVertex2f(-1.3, -0.7);
	glEnd();
	glTranslated(-1.6, 1.5, 0);
	glRotated(-27, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glColor3f(0.6f, 0.0f, 0.0f);
	glVertex2f(-0.6f, -0.6f);
	glVertex2f(0.6f, -0.6f);
	glVertex2f(0.0f, 0.6f);
	glEnd();
	glTranslated(1.2, -0.2, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.4f, -0.4f);
	glVertex2f(0.4f, -0.4f);
	glVertex2f(0.0f, 0.4f);
	glEnd();
	glTranslated(0, -2, 0);
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.5, 0.8);
	glVertex2f(0.5, -0.8);
	glEnd();
	glTranslated(-0.7, 3.3, 0);
	glRotated(-235, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glColor3f(0.6f, 0.0f, 0.0f);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.0f, 0.5f);
	glEnd();
	glTranslated(-0.9, -0.2, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(0.6f, 0.0f, 0.0f);
	glVertex2f(-0.3f, -0.3f);
	glVertex2f(0.3f, -0.3f);
	glVertex2f(0.0f, 0.3f);
	glEnd();
	glPopMatrix();
	glLineWidth(1.0f);
	/*
	int gotDamaged = 0;
	for (int i = 0; i < 4; i++) {
		if (centerX >= genXObstacle[i] - 10 && centerX <= genXObstacle[i] + 12)
			if (centerY >= genYObstacle[i] - 10 && centerY <= genYObstacle[i] + 12) {
				gotDamaged = 1;
				if (damaged == 0 && !staredEffect) {
					printf(" case 1\n");
					health--;
					damaged = 1;
					continue;
				}
			}
		if ((minX >= genXObstacle[i] - 10 && minX <= genXObstacle[i] + 12) || (maxX >= genXObstacle[i] - 10 && maxX <= genXObstacle[i] + 12))
			if (minY >= genYObstacle[i] - 10 && minY <= genYObstacle[i] + 12 || (maxY >= genYObstacle[i] - 10 && maxY <= genYObstacle[i] + 12)) {
				gotDamaged = 1;
					if (damaged == 0 && !staredEffect) {
						printf(" case 2\n");
							health--;
							damaged = 1;
					}
			}

	}
	if (!gotDamaged)
		damaged = 0;*/

	for (int i = 0; i < 8; i++) {
		if (genXCollect[i] == NULL)
			continue;
		if (centerX >= genXCollect[i] && centerX <= genXCollect[i] + 25 || centerX >= genXCollect[i] - 15 && centerX <= genXCollect[i] + 15)
			if (centerY >= genYCollect[i] && centerY <= genYCollect[i] + 25 || centerY >= genYCollect[i] - 25 && centerY <= genYCollect[i] + 25) {
				if (i > 3) {
					Mix_PlayChannel(-1, coin, 0);
					score++;
					genXCollect[i] = NULL;
					continue;
				}
				Mix_PlayChannel(-1, powerUp, 0);
				if (i % 2 == 1) {
					staredEffect = 1;
					staredTime = 5;
					genXCollect[i] = NULL;
					continue;
				}
				printf(" case 1\n");
				genXCollect[i] = NULL;
				timeCurr += 10;
				continue;
			}
		if ((minX >= genXCollect[i] && minX <= genXCollect[i] + 25))
			if (minY >= genYCollect[i] && minY <= genYCollect[i] + 25) {
				if (i > 3) {
					Mix_PlayChannel(-1, coin, 0);
					score++;
					genXCollect[i] = NULL;
					continue;
				}
				Mix_PlayChannel(-1, powerUp, 0);
				if (i % 2 == 1) {
					staredEffect = 1;
					genXCollect[i] = NULL;
					staredTime = 5;
					continue;
				}
				printf(" case 2\n");
				genXCollect[i] = NULL;
				timeCurr += 10;
				continue;
			}
		if ((maxX >= genXCollect[i] && maxX <= genXCollect[i] + 25))
			if (maxY >= genYCollect[i] && maxY <= genYCollect[i] + 25) {
				if (i > 3) {
					Mix_PlayChannel(-1, coin, 0);
					score++;
					genXCollect[i] = NULL;
					continue;
				}
				Mix_PlayChannel(-1, powerUp, 0);
				if (i % 2 == 1) {
					staredEffect = 1;
					genXCollect[i] = NULL;
					staredTime = 5;
					continue;
				}
				printf(" case 3\n");
				genXCollect[i] = NULL;
				timeCurr += 10;
			}
	}

	if (health == 0) {
		gameOver = 1;
	}
	if (timeCurr <= 0) {
		gameOver = 1;
	}

	if (((minX >= 600 && minX <= 630) || (maxX >= 600 && maxX <= 630)) && score >= 2)
		if ((minY >= 400 && minY <= 430) || (maxY >= 400 && maxY <= 430)) {
			gameOver = 1;
			won = 1;
		}
	if (centerX >= 600 && centerX <= 630 && score >= 2)
		if (centerY >= 400 && centerY <= 430) {
			gameOver = 1;
			won = 1;
		}

	glFlush();
}

void starColor(int i) {
	red = getRandomFloat();
	green = getRandomFloat();
	blue = getRandomFloat();
	glutTimerFunc(90, starColor, 11);
	glutPostRedisplay();
}

void rotInterval(int i) {
	rotAnim += 10;
	glutTimerFunc(50, rotInterval, 11);
	glutPostRedisplay();
}

void ScaleInterval(int i) {
	if (ScaleAnim >= 1.35)
		scaleUp = 0;
	if (ScaleAnim == 1)
		scaleUp = 1;
	if (scaleUp == 1)
		ScaleAnim += 0.01;
	else
		ScaleAnim -= 0.01;
	glutTimerFunc(25, ScaleInterval, 11);
	glutPostRedisplay();
}

void BackInterval(int i) {
	changeDirec++;
	if (changeDirec >= changeVal) {
		if (direc == 0) direc = 1;
		else direc = 0;
		changeDirec = 0;
		if (changeVal > 200)
			changeVal /= 2;
		else
			changeVal *= 2;
	}
	if (direc == 1) {
		translateOne += 10;
		translateTwo += 10;
		if (translateOne >= 700)
			translateOne = -700;
		if (translateTwo >= 700)
			translateTwo = -700;
	}
	else {
		translateOne -= 10;
		translateTwo -= 10;
		if (translateOne <= -700)
			translateOne = 700;
		if (translateTwo <= -700)
			translateTwo = 700;
	}
	glutTimerFunc(backRef, BackInterval, 11);
	glutPostRedisplay();
}

int validNewObject(int x, int y) {
	printf(" %d x %d y ", x, y);
	int minX = 280;
	int maxX = 400;
	int minY = 210;
	int maxY = 330;
	int minXEnd = 600;
	int minYEnd = 400;
	if (y < 90 && x >= 460 && x <= 535)
		return 0;
	if (y < 90 && x >= 165 && x <= 230)
		return 0;
	if (x < 100 || x > 640 || y < 60 || y > 450)
		return 0;
	if (x >= minX && x <= maxX && y >= minY && y <= maxY)
		return 0;

	//if ((x >= minXEnd && x <= minXEnd + 30 || x + 25 >= minXEnd && x + 25 <= minXEnd + 30) &&(y >= minYEnd && y <= minYEnd + 30 || y + 25 >= minYEnd && y + 25 <= minYEnd + 30) )
		//return 0;
	//if (y >= minYEnd && y <= minYEnd + 30 || y + 25 >= minYEnd && y + 25 <= minYEnd + 30)
		//return 0;
	for (int i = 0; i < 8; i++) {
		if (genXCollect[i] == NULL)
			continue;
		if (x >= genXCollect[i] && x <= genXCollect[i] + 30 || x + 25 >= genXCollect[i] && x + 25 <= genXCollect[i] + 30 || (x - 10 >= genXCollect[i] && x - 10 <= genXCollect[i] + 30))
			if (y >= genYCollect[i] && y <= genYCollect[i] + 30 || y + 25 >= genYCollect[i] && y + 25 <= genYCollect[i] + 30 || x - 10 >= genXCollect[i] && x - 10 <= genXCollect[i] + 30)
				return 0;
	}
	for (int i = 0; i < 4; i++) {
		if (x >= genXObstacle[i] - 40 && x <= genXObstacle[i] + 40 || x - 10 >= genXObstacle[i] - 40 && x - 12 <= genXObstacle[i] + 40)
			if (y >= genYObstacle[i] - 40 && y <= genYObstacle[i] + 40 || y - 25 >= genYObstacle[i] - 40 && y - 12 <= genYObstacle[i] + 40)
				return 0;
	}
	
	return 1;
}

void generateStars() {
	for (int i = 0; i < 100;i++) {
		int x = distributionXStars(generator);
		int y = distributionYStars(generator);
		genXStars[i] = x;
		genYStars[i] = y;
	}
}

void generateCollectables() {
	int minX = (-3.0 * 10) + posX;
	int maxX = (3 * 10) + posX;
	int minY = (-2.5 * 10) + posY;
	int maxY = (3 * 10) + posY;
	int centerX = posX;
	int centerY = posY;
	for (int i = 0; i < 8; i++) {
		int generatedX = distributionX(generator);
		int generatedY = distributionY(generator);
		if (!(validNewObject(generatedX, generatedY))) {
			i--;
			continue;
		}
		genXCollect[i] = generatedX;
		genYCollect[i] = generatedY;
	}
}

void generateObstacles() {
	int minX = (-3.0 * 10) + 40;
	int maxX = (3 * 10) + 40;
	int minY = (-2.5 * 10) + 40;
	int maxY = (3 * 10) + 40;
	int centerX = 40;
	int centerY = 40;
	for (int i = 0; i < 4; i++) {
		int generatedX = distributionX(generator);
		int generatedY = distributionY(generator);
		if (!(validNewObject(generatedX, generatedY))) {
			i--;
			continue;
		}
		genXObstacle[i] = generatedX;
		genYObstacle[i] = generatedY;
	}
}


void SDLmain(int argc, char **argr) {
	glutInit(&argc, argr);
	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music* music = Mix_LoadMUS("PACMAN_PHONK.wav");
	loseMusic = Mix_LoadMUS("mario.wav");
	winMusic = Mix_LoadMUS("farewell.wav");
	Mix_PlayMusic(music, -1);
	bruh = Mix_LoadWAV("Bruh.wav");
	coin = Mix_LoadWAV("marioCoin.wav");
	powerUp = Mix_LoadWAV("marioPowerUp.wav");


	glutInitWindowSize(700, 500);
	glutInitWindowPosition(500, 100);
	red = getRandomFloat();
	green = getRandomFloat();
	blue = getRandomFloat();
	generateStars();
	generateCollectables();
	//generateObstacles();
	glutCreateWindow("Evil Pacman");
	glutDisplayFunc(Display);
	glutKeyboardFunc(key);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutTimerFunc(5000, BackInterval, 11);
	glutTimerFunc(0, setTime, 200);
	glutTimerFunc(1000, rotInterval, 200);
	glutTimerFunc(2000, ScaleInterval, 100);
	glutTimerFunc(4000, starColor, 100);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 700, 0.0, 500);

	glutMainLoop();
	
	std::exit(0);
}

int main(int argc, char** argr) {
	SDLmain(argc, argr);
	return (0);
}
