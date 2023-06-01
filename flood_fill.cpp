#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;

struct Point
{
    int x;
    int y;
};
struct Color
{
    float r;
    float g;
    float b;
};

Color getPixelColor(int x, int y)
{
    Color color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}
void setPixelColor(int x, int y, Color color)
{
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}
void FloodFill(int x, int y, Color oldColor, Color newColor)
{
    Color color;
    color = getPixelColor(x, y);
    if (color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b)
    {

        setPixelColor(x, y, newColor);
        FloodFill(x + 1, y, oldColor, newColor);
        FloodFill(x, y + 1, oldColor, newColor);
        FloodFill(x - 1, y, oldColor, newColor);
        FloodFill(x, y - 1, oldColor, newColor);
      
    }
    return;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    glVertex2i(250, 250);
    glVertex2i(250, 300);
    glVertex2i(300, 300);
    glVertex2i(300, 250);
    glEnd();
    glFlush();
}
void myinit()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(1.0);
    gluOrtho2D(0.0, 650.0, 0.0, 650.0);
}
void MYmouse(int button, int state, int x, int y)
{
    Color newColor = {0.0f, 1.0f, 0.0f};
    Color oldColor = {0.0f, 0.0f, 0.0f};
    Color bColor = {1.0f, 1.0f, 1.0f};
    Color oColor = {1.0f, 0.0f, 0.0f};

    FloodFill(x, 650 - y, oldColor, newColor);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(650, 650);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Polygon filling");
    cout << "1.Flood Fill Algorithm\n";

    glutDisplayFunc(display);

    glutMouseFunc(MYmouse);
    myinit();
    glutMainLoop();
    return 0;
}
