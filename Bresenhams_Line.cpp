#include <iostream>
#include <GL/glut.h>
#include <math.h>
#define ROUND(X)((int)X+0.5)
using namespace std;
static int menu_id;
static int submenu_id1;
static int submenu_id2;
int w = 640;
int h = 480;


void BH_dotted(float, float, float, float);
void BH_dashed(float, float, float, float);
void BH_simple(float, float, float, float);
void BH_solid(float, float, float, float);

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0); 
	glColor3f(0.0, 0.0, 0.0); 
	glPointSize(4.0);
	gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2); 
}
void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glVertex2d(-w / 2, 0);
	glVertex2d(w / 2, 0);
	glVertex2d(0, -h / 2);
	glVertex2d(0, h / 2);
	glEnd();
	glFlush();
}


void BH_simple(float x1, float y1, float x2, float y2)
{
	float dx, dy, di, ds, dt;
	int count = 0;
	dx = x2 - x1;
	dy = y2 - y1;
	di = (2 * (dy)) - (dx); 
	ds = 2 * (dy);  
	dt = 2 * ((dy)-(dx));  
	glPointSize(4.0);
	glBegin(GL_POINTS);
	glVertex2f(x1, y1);
	glEnd();
	while (x1 < x2)
	{
		x1++;
		if (di < 0)  
		{
			di += ds;
		}
		else  
		{
			y1++;
			di += dt;
		}
		glPointSize(4.0);
		glBegin(GL_POINTS);
		glVertex2f(x1, y1);
		glEnd();
	}
}
void BH_dashed(float x1, float y1, float x2, float y2)
{
	float dx, dy, di, ds, dt;
	int count = 0;
	dx = x2 - x1;
	dy = y2 - y1;
	di = (2 * dy) - dx;
	ds = 2 * dy;
	dt = 2 * (dy - dx);
	glPointSize(4.0);
	glBegin(GL_POINTS);
	glVertex2f(x1, y1);
	glEnd();
	count = 1;
	while (x1 < x2)
	{
		x1++;
		if (di < 0)
		{
			di += ds;
		}
		else
		{
			y1++;
			di += dt;
		}
		if (count < 6)  
		{
			glPointSize(4.0);
			glBegin(GL_POINTS);
			glVertex2f(x1, y1);
			glEnd();
			count++;
		}
		if (count >= 6)
		{
			count++;  
			if (count == 12)
			{
				count = 0;
			}
		}
	}
}
void BH_dotted(float x1, float y1, float x2, float y2)
{
	float dx, dy, di, ds, dt;
	int count = 0;
	dx = x2 - x1;
	dy = y2 - y1;
	di = (2 * dy) - dx;
	ds = 2 * dy;
	dt = 2 * (dy - dx);
	glPointSize(4.0);
	glBegin(GL_POINTS);
	glVertex2f(x1, y1);
	glEnd();
	count = 1;
	while (x1 < x2)
	{
		x1++;
		if (di < 0)
		{
			di += ds;
		}
		else
		{
			y1++;
			di += dt;
		}
		if (count % 10 == 0)
		{
			glPointSize(4.0);
			glBegin(GL_POINTS);
			glVertex2f(x1, y1);
			glEnd();
		}
		count++;
	}
}


void BH_solid(float x1, float y1, float x2, float y2)
{
	float dx, dy, di, ds, dt;
	int count = 0;
	dx = x2 - x1;
	dy = y2 - y1;
	di = (2 * dy) - dx;
	ds = 2 * dy;
	dt = 2 * (dy - dx);
	glPointSize(7.0);
	glBegin(GL_POINTS);
	glVertex2f(x1, y1);
	glEnd();
	while (x1 < x2)
	{
		x1++;
		if (di < 0)
		{
			di += ds;
		}
		else
		{
			y1++;
			di += dt;
		}
		glPointSize(8.0);
		glBegin(GL_POINTS);
		glVertex2f(x1, y1);
		glEnd();
	}
}


void menu_bh(int a)
{
	switch (a)
	{
	case 1:
		BH_simple(10, 50, 150, 200);
		break;
	case 2:
		BH_dashed(10, 50, 150, 200);
		break;
	case 3:
		BH_dotted(10, 50, 150, 200);
		break;
	case 4:
		BH_solid(10, 50, 150, 200);
		break;
	}

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(" Bresenham");
	glutDisplayFunc(draw);


	submenu_id2 = glutCreateMenu(menu_bh);
	glutAddMenuEntry("1.Simple Line", 1);
	glutAddMenuEntry("2.Dashed Line", 2);
	glutAddMenuEntry("3.Dotted Line", 3);
	glutAddMenuEntry("4.Solid Line", 4);

	menu_id = glutCreateMenu(menu_bh);

	glutAddSubMenu("Bresenham Algorithm", submenu_id2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	init();
	glutMainLoop();
	return(0);

}
