#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>
#include <iostream>


double merk = 0;
double ven = 0;
double bumi = 0;
double mars = 0;
double s1 = 0;

int i;
const double PI = 3.141592653589793;
void orbit(int jari2, int jumlah_titik, int x_tengah, int y_tengah) {
	glBegin(GL_POLYGON);
	for (i = 0; i <= 360; i++) {
		float sudut = i * (2 * PI / jumlah_titik);
		float x = x_tengah + jari2 * cos(sudut);
		float y = y_tengah + jari2 * sin(sudut);
		glVertex2f(x, y);
	}
	glEnd();
}

void utama(void) {

	glClear(GL_COLOR_BUFFER_BIT);

	glColor4f(0.3, 0.3, 0.3, 20);
	glBegin(GL_LINES);
	glVertex2f(50, 50);
	glVertex2f(sin(merk) * 10 + 50, cos(merk) * 10 + 50);//merkurius
	glEnd();

	//garis dari matahari ke planet
	glColor4f(0.3, 0.3, 0.3, 20);
	glBegin(GL_LINES);
	glVertex2f(50, 50);
	glVertex2f(sin(merk) * 10 + 50, cos(merk) * 10 + 50);//merkurius
	glEnd();

	glColor4f(0.3, 0.3, 0.3, 20);
	glBegin(GL_LINES);
	glVertex2f(50, 50);
	glVertex2f(sin(ven) * 20 + 50, cos(ven) * 20 + 50);//venus
	glEnd();

	glColor4f(0.3, 0.3, 0.3, 20);
	glBegin(GL_LINES);
	glVertex2f(50, 50);
	glVertex2f(sin(bumi) * 30 + 50, cos(bumi) * 30 + 50);//bumi
	glEnd();

	glColor4f(0.3, 0.3, 0.3, 20);
	glBegin(GL_LINES);
	glVertex2f(50, 50);
	glVertex2f(sin(mars) * 45 + 50, cos(mars) * 45 + 50);//mars
	glEnd();
	//garis dari matahari ke planet

	//garis orbit planet
	glColor4f(0.1, 0.1, 0.1, 10);
	glBegin(GL_LINE_STRIP);//merkurius
	orbit(10, 80, 50, 50);
	glEnd();

	glBegin(GL_LINE_STRIP);//venus
	orbit(20, 80, 50, 50);
	glEnd();

	glBegin(GL_LINE_STRIP);//bumi 
	orbit(30, 80, 50, 50);
	glEnd();

	glBegin(GL_LINE_STRIP);//mars
	orbit(45, 80, 50, 50);
	glEnd();
	//garis orbit planet

	//rotasi planet
	glEnable(GL_POINT_SMOOTH);
	glPointSize(60);
	glBegin(GL_POINTS);
	glColor3f(1, 1, 0);
	glVertex2f(50, 50);//matahari
	glEnd();

	glPointSize(8);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex2f(sin(merk) * 10 + 50, cos(merk) * 10 + 50);//merkurius
	glEnd();

	glPointSize(15);
	glBegin(GL_POINTS);
	glColor3f(0, 1, 0);
	glVertex2f(sin(ven) * 20 + 50, cos(ven) * 20 + 50);//venus
	glEnd();

	glPointSize(20);
	glBegin(GL_POINTS);
	glColor3f(0, 1, 1);
	glVertex2f(sin(bumi) * 30 + 50, cos(bumi) * 30 + 50);//bumi
	glEnd();

	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(1, 1, 1);
	glVertex2f(sin(mars) * 45 + 50, cos(mars) * 45 + 50);//mars
	glEnd();
	glFlush();
	//rotasi planet
}

void kedua(int) {

	glutPostRedisplay();
	glutTimerFunc(15, kedua, 1);
		merk += 0.05f;
		ven += 0.025f;
		bumi += 0.011f;
		mars += 0.005f;
		s1 += 0.010f;
	}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(480, 150);
	glutInitWindowSize(800, 800);
	glutCreateWindow(argv[0]);
	gluOrtho2D(0, 100, 100, 0);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutTimerFunc(15, kedua, 1);
	glutDisplayFunc(utama);
	glutMainLoop();

	return(0);
}


/*#include <iostream>
#include <GL/freeglut.h>
#include <math.h>

float x_pos = 0.0f;
float y_pos = 0.0f;
float deltax = 0.0097f;
float deltay = 0.030f;
bool toRight = true;
bool omega = true;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POINTS);
	glVertex2f(x_pos, sin(y_pos));
	glEnd();
	glutSwapBuffers();
}

void myinit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(8.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0, 1.0);
}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 30, timer, 0);

	if (omega == true) {

		y_pos += deltay;
		if (x_pos < 1.0f && toRight)
			x_pos += deltax;
		else
			toRight = false;

		if (x_pos > -1.0f && !toRight)
			x_pos -= deltax;
		else
			toRight = true;
	}
}

void key(unsigned char key, int, int) {
	if (key == 'p' || key == 'P') {
		omega = !omega;
	}
	std::cout << key << " " << std::endl;
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Tugas 3 Grafkom");

	glutDisplayFunc(display);

	myinit();
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(key);
	glutMainLoop();

	return 0;
}
*/
