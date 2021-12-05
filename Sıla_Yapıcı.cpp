

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 600

#define TIMER_PERIOD   16 // period for the timer
#define TIMER_ON        0 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; //current Window width and height

double x2, y2;

/*****
   to draw circle (DAIRE), center at (x,y) radius r
*****/
void circle(int x, int y, int r) {
#define PI 3.1415
	float angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++) {
		angle = 2 * PI*i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

/*****
   to draw circle wire (CEMBER), center at (x,y) radius r
*****/
void circle_wire(int x, int y, int r) {
#define PI 3.1415
	float angle;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 100; i++) {
		angle = 2 * PI*i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

void print(int x, int y, const char *string, void *font) {
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}

/*****
   to display text with variables
vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
*****/
void vprint(int x, int y, void *font, const char *string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, str[i]);
	}
}

/*****
   vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
*****/
void vprint2(int x, int y, float size, const char *string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i < len; i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}

/*****
   to display onto window using OpenGL commands
*****/
void display() {
	//clear window to black
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(50, 100, 0);
	glRotatef(45, 0, 0, 1);
	glScalef(6, 5, 1);



	
	glLoadIdentity();
	int a;
	glColor3ub(50, 50, 50);
	for (a = -240; a <= 240; a += 30)
	{
		glBegin(GL_LINES);
		glVertex2f(a, 5);
		glVertex2f(a, -5);
		glVertex2f(5, a);
		glVertex2f(-5, a);
		glEnd();
		if(a > 0)
		{
			vprint(-27, a - 3, GLUT_BITMAP_HELVETICA_12, "%d", a);
			vprint(a - 6, 12, GLUT_BITMAP_HELVETICA_12, "%d", a);
		}
		else if (a < 0) {
		vprint(12, a - 3, GLUT_BITMAP_HELVETICA_12, "%d", a);
		vprint(a - 13, -20, GLUT_BITMAP_HELVETICA_12, "%d", a);
		}
	}vprint(4, 7, GLUT_BITMAP_HELVETICA_12, "0");

	glBegin(GL_LINES);
	glVertex2f(0, 270);
	glVertex2f(0, -270);
	glVertex2f(270, 0);
	glVertex2f(-270, 0);
	glEnd();



	glColor3f(0, 0.5, 0.8);
	vprint(-270, -270, GLUT_BITMAP_HELVETICA_18, "x = %.0lf  y = %.0lf", x2, y2);
	glutSwapBuffers();
}

/*****
   key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
*****/
void onKeyDown(unsigned char key, int x, int y) {
	//exit when ESC is pressed.
	if (key == 27)
		exit(0);

	//to refresh the window it calls display() function
	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y) {
	//exit when ESC is pressed.
	if (key == 27)
		exit(0);

	//to refresh the window it calls display() function
	glutPostRedisplay();
}

/*****
   special Key like GLUT_KEY_F1, F2, F3,...
   arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
*****/
void onSpecialKeyDown(int key, int x, int y) {
	//write your codes here.

	switch (key) {
	case GLUT_KEY_UP: up = true; break;
	case GLUT_KEY_DOWN: down = true; break;
	case GLUT_KEY_LEFT: left = true; break;
	case GLUT_KEY_RIGHT: right = true; break;
	}

	//to refresh the window it calls display() function
	glutPostRedisplay();
}

/*****
   special Key like GLUT_KEY_F1, F2, F3,...
   arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
*****/
void onSpecialKeyUp(int key, int x, int y) {
	//write your codes here

	switch (key) {
	case GLUT_KEY_UP: up = false; break;
	case GLUT_KEY_DOWN: down = false; break;
	case GLUT_KEY_LEFT: left = false; break;
	case GLUT_KEY_RIGHT: right = false; break;
	}

	//to refresh the window it calls display() function
	glutPostRedisplay();
}

/*****
   When a click occurs in the window,
   It provides which button
   buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
   states  : GLUT_UP , GLUT_DOWN
   x, y is the coordinate of the point that mouse clicked
*****/
void onClick(int button, int stat, int x, int y) {
	//write your codes here.



	//to refresh the window it calls display() function
	glutPostRedisplay();
}

/*****
   This function is called when the window size changes.
   w : is the new width of the window in pixels
   h : is the new height of the window in pixels
*****/
void onResize(int w, int h) {
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); //refresh window
}

void onMoveDown(int x, int y) {
	//write your codes here.



	//to refresh the window it calls display() function	
	glutPostRedisplay();
}

/*****
   GLUT to OpenGL coordinate conversion
   x2 = x1 - winWidth / 2
   y2 = winHeight / 2 - y1
*****/
void onMove(int x, int y) {
	//write your codes here.

	x2 = x - winWidth / 2;
	y2 = winHeight / 2 - y;


	//to refresh the window it calls display() function
	glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	//write your codes here


	//to refresh the window it calls display() function
	glutPostRedisplay(); //display()

}
#endif

void init() {
	//smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sýla Yapýcý");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	//keyboard registration
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);

	//mouse registration
	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);

#if TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	init();

	glutMainLoop();

}
