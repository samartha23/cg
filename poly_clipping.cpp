#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
using namespace std;

typedef struct 
{
    float x;
    float y;
} PT;



int n;

int i, j;

PT p1, p2, p[20], pp[20];

void left() // left clipper
{
    i = 0;
    j = 0;

    for (i = 0; i < n; i++)
    {
        if (p[i].x < p1.x && p[i + 1].x >= p1.x) // Case-1: outside to inside
        {
            if (p[i + 1].x - p[i].x != 0)
            {
                pp[j].y = (p[i + 1].y - p[i].y) / (p[i + 1].x - p[i].x) * (p1.x - p[i].x) + p[i].y; 
            }
            else
            {
                pp[j].y = p[i].y;
            }
            pp[j].x = p1.x;
            j++;
            pp[j].x = p[i + 1].x;
            pp[j].y = p[i + 1].y;
            j++;
        }

        if (p[i].x >= p1.x && p[i + 1].x >= p1.x) // Case-2: inside to inside
        {
            pp[j].y = p[i + 1].y; 
            pp[j].x = p[i + 1].x;
            j++;
        }

        if (p[i].x >= p1.x && p[i + 1].x < p1.x) // Case-3: inside to outside
        {
            if (p[i + 1].x - p[i].x != 0)
            {
                pp[j].y = (p[i + 1].y - p[i].y) / (p[i + 1].x - p[i].x) * (p1.x - p[i].x) + p[i].y; 
            }
            else
            {
                pp[j].y = p[i].y;
            }
            pp[j].x = p1.x;
            j++;
        }
    }

    for (i = 0; i < j; i++)
    {
        p[i].x = pp[i].x;
        p[i].y = pp[i].y;
    }

    p[i].x = pp[0].x;
    p[i].y = pp[0].y;
    n = j;
}

void right() // right clipper
{
    i = 0;
    j = 0;

    for (i = 0; i < n; i++)
    {
        if (p[i].x > p2.x && p[i + 1].x <= p2.x) // Case-1: outside to inside
        {
            if (p[i + 1].x - p[i].x != 0)
            {
                pp[j].y = (p[i + 1].y - p[i].y) / (p[i + 1].x - p[i].x) * (p2.x - p[i].x) + p[i].y; 
            }
            else
            {
                pp[j].y = p[i].y;
            }
            pp[j].x = p2.x;
            j++;
            pp[j].x = p[i + 1].x;
            pp[j].y = p[i + 1].y;
            j++;
        }

        if (p[i].x <= p2.x && p[i + 1].x <= p2.x) // Case-2: inside to inside
        {
            pp[j].y = p[i + 1].y; 
            pp[j].x = p[i + 1].x;
            j++;
        }

        if (p[i].x <= p2.x && p[i + 1].x > p2.x) // Case-3: inside to outside
        {
            if (p[i + 1].x - p[i].x != 0)
            {
                pp[j].y = (p[i + 1].y - p[i].y) / (p[i + 1].x - p[i].x) * (p2.x - p[i].x) + p[i].y; 
            }
            else
            {
                pp[j].y = p[i].y;
            }
            pp[j].x = p2.x;
            j++;
        }
    }

    for (i = 0; i < j; i++)
    {
        p[i].x = pp[i].x;
        p[i].y = pp[i].y;
    }

    p[i].x = pp[0].x;
    p[i].y = pp[0].y;
}

void top() // top clipper
{
    i = 0;
    j = 0;

    for (i = 0; i < n; i++)
    {
        if (p[i].y > p2.y && p[i + 1].y <= p2.y) // Case-1: outside to inside
        {
            if (p[i + 1].y - p[i].y != 0)
            {
                pp[j].x = (p[i + 1].x - p[i].x) / (p[i + 1].y - p[i].y) * (p2.y - p[i].y) + p[i].x; 
            }
            else
            {
                pp[j].x = p[i].x;
            }
            pp[j].y = p2.y;
            j++;
            pp[j].x = p[i + 1].x; 
            pp[j].y = p[i + 1].y;
            j++;
        }

        if (p[i].y <= p2.y && p[i + 1].y <= p2.y) // Case-2: inside to inside
        {
            pp[j].y = p[i + 1].y; 
            pp[j].x = p[i + 1].x;
            j++;
        }

        if (p[i].y <= p2.y && p[i + 1].y > p2.y) // Case-3: inside to outside
        {
            if (p[i + 1].y - p[i].y != 0)
            {
                pp[j].x = (p[i + 1].x - p[i].x) / (p[i + 1].y - p[i].y) * (p2.y - p[i].y) + p[i].x;
            }
            else
            {
                pp[j].x = p[i].x;
            }
            pp[j].y = p2.y;
            j++;
        }
    }

    for (i = 0; i < j; i++)
    {
        p[i].x = pp[i].x;
        p[i].y = pp[i].y;
    }

    p[i].x = pp[0].x;
    p[i].y = pp[0].y;
    n = j;
}

void bottom() // bottom clipper
{
    i = 0;
    j = 0;

    for (i = 0; i < n; i++)
    {
        if (p[i].y < p1.y && p[i + 1].y >= p1.y) // Case-1: outside to inside
        {
            if (p[i + 1].y - p[i].y != 0)
            {
                pp[j].x = (p[i + 1].x - p[i].x) / (p[i + 1].y - p[i].y) * (p1.y - p[i].y) + p[i].x;
            }
            else
            {
                pp[j].x = p[i].x;
            }
            pp[j].y = p1.y;
            j++;
            pp[j].x = p[i + 1].x; 
            pp[j].y = p[i + 1].y;
            j++;
        }

        if (p[i].y >= p1.y && p[i + 1].y >= p1.y) // Case-2: inside to inside
        {
            pp[j].x = p[i + 1].x; 
            pp[j].y = p[i + 1].y;
            j++;
        }

        if (p[i].y >= p1.y && p[i + 1].y < p1.y) // Case-3: inside to outside
        {
            if (p[i + 1].y - p[i].y != 0)
            {
                pp[j].x = (p[i + 1].x - p[i].x) / (p[i + 1].y - p[i].y) * (p1.y - p[i].y) + p[i].x; 
            }
            else
            {
                pp[j].x = p[i].x;
            }
            pp[j].y = p1.y;
            j++;
        }
    }

    for (i = 0; i < j; i++)
    {
        p[i].x = pp[i].x;
        p[i].y = pp[i].y;
    }
    p[i].x = pp[0].x;
    p[i].y = pp[0].y;
    n = j;
}

void drawpolygon()
{
    glColor3f(1.0, 0.0, 0.0);
    for (i = 0; i < n - 1; i++)
    {
        glBegin(GL_LINES);
        glVertex2d(p[i].x, p[i].y);
        glVertex2d(p[i + 1].x, p[i + 1].y);
        glEnd();
    }
    glBegin(GL_LINES);
    glVertex2d(p[i].x, p[i].y);
    glVertex2d(p[0].x, p[0].y);
    glEnd();
}

void myMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_LINE_LOOP);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p1.y);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p1.x, p2.y);
        glEnd();
        left();
        right();
        top();
        bottom();
        drawpolygon();
    }
    glFlush();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.4, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p1.x, p2.y);
    glEnd();
    drawpolygon();
    glFlush();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); 
    gluOrtho2D(-500, 500, -500, 500);
}

int main(int argc, char **argv)
{
    cout<<"Enter Window Coordinates : "<<endl ;
    cout<<"Please Enter two Points:\n"; 
    cout<<"Enter P1(x,y) : ";
    cin>>p1.x>>p1.y;

   cout<<"Enter P2(x,y):\n"; 
    cin>>p2.x>>p2.y;

    cout<<"\nEnter the no. of vertices : "; 
    cin>>n;

    for (i = 0; i < n; i++)
    {
       cout<<"\nEnter the coordinate of vertices ";
        cin>>p[i].x;
        cin>>p[i].y;
    }

    p[i].x = p[0].x; 
    p[i].y = p[0].y;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Sutherland Hodgman Polygon Clipping Algorithm ");
    init();

    glutDisplayFunc(display);
    glutMouseFunc(myMouse); 
    glFlush();
    glutMainLoop();
    return 0;
}
