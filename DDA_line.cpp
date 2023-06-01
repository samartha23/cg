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
void DDA_simple(float,float,float,float);
void DDA_dashed(float, float, float, float);
void DDA_dotted(float, float, float, float);
void DDA_solid(float, float, float, float);



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
void DDA_simple(float x1,float y1,float x2,float y2)
{
	float dx, dy, X, Y,steps, xinc, yinc;
	int i = 0;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) >= abs(dy))
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}

	xinc = dx / steps;
	yinc = dy / steps;
	X = x1;  
	Y = y1;
	glPointSize(4.0);
	glBegin(GL_POINTS);
	glVertex2f(ROUND(X), ROUND(Y));
	glEnd();
	i = 1;
	while (i <= steps)
	{
		glPointSize(4.0);
		glBegin(GL_POINTS);
		glVertex2f(ROUND(X), ROUND(Y));
		glEnd();
		X = X + xinc;  
		Y = Y + yinc;
		glFlush();
		i++;
	}
}

void DDA_dashed(float x1, float y1, float x2, float y2)
{
	float dx, dy, X, Y,steps;
	int i = 0;
	int count = 0;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) >= abs(dy))
	{
		steps = abs(dx);
	}
	else {
		steps = abs(dy);
	}
	dx= dx / steps;
	dy = dy / steps;
	X = x1;
	Y = y1;
	glBegin(GL_POINTS);
	glVertex2f(ROUND(X), ROUND(Y));
	glEnd();
	glFlush();
	i = 1;
	count = 1;
	while(i<=steps)
	{
		X = X + dx;
		Y = Y + dy;
		if (count<=10) 
		{
			glBegin(GL_POINTS);
			glVertex2f(ROUND(X), ROUND(Y));
			glEnd();
			glFlush();
			count++;
		}
		if (count >= 10) 
		{
			count++;  
			if (count == 20) 
			{
				count = 1;
			}
		}
		i++;
	}


}
void DDA_dotted(float x1, float y1, float x2, float y2)
{
	float dx, dy, X, Y, steps;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) >= abs(dy))
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}
	dx = dx / steps;
	dy = dy / steps;
	X = x1;
	Y = y1;
	glBegin(GL_POINTS);
	glVertex2f(ROUND(X), ROUND(Y));
	glEnd();
	int count = 1;
	int i = 1;
	while (i <= steps)
	{
		X = X + dx;
		Y = Y + dy;
		if (count % 10 == 0)   
		{
			glBegin(GL_POINTS);
			glVertex2f(ROUND(X), ROUND(Y));
			glEnd();
			glFlush();
		}
		count++;
		i++;
	}


}

void DDA_solid(float x1, float y1, float x2, float y2)
{
	float dx, dy, steps, X, Y;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) >= abs(dy))
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}
	dx = dx / steps;
	dy = dy / steps;
	X = x1;
	Y = y1;
	int i = 0;
	while (i <= steps)
	{
		glPointSize(8.0); 
		glBegin(GL_POINTS);
		glVertex2f(ROUND(X), ROUND(Y));
		glEnd();
		X = X + dx;
		Y = Y + dy;
		glFlush();
		i++;
	}
}



void menu_dda(int a)
{
	switch (a)
	{
	case 1:
		DDA_simple(-10, 50, 150, 190);
		break;
	case 2:
		DDA_dashed(20, -60, 150, 200);
		break;
	case 3:
		DDA_dotted(10,- 45, 150, 189);
		break;
	case 4:
		DDA_solid(15, 60, 150, 200);
		break;
	}

}




int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("DDA ");
	glutDisplayFunc(draw);
	submenu_id1=glutCreateMenu(menu_dda);
	glutAddMenuEntry("1.Simple Line", 1);
	glutAddMenuEntry("2.Dashed Line", 2);
	glutAddMenuEntry("3.Dotted Line", 3);
	glutAddMenuEntry("4.Solid Line", 4);


	menu_id = glutCreateMenu(menu_dda);
	glutAddSubMenu("DDA Algorithm", submenu_id1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	init();
	glutMainLoop();
	return(0);

}
