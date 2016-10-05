#include "stdafx.h"
#include "DrawLib.h"
typedef unsigned char uchar;
Point2i corner[2];

bool selected=false;
void mykeyboard(uchar key,int x,int y)
{
	y=WIN_H-y;

	switch(key)
	{
	case 'b':
		DrawLib::drawPoints2i(x,y,Color3f(1.0f,1.0f,1.0f));
		glutSwapBuffers();
		break;
	case 'q':
		break;
	}
}

void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f,1.0f,1.0f);

	if(selected)
	{
		glRecti(corner[0].x,corner[0].y,corner[1].x,corner[1].y);
	}
	glutSwapBuffers();// Ω´ªÊÕºª∫¥ÊøΩ±¥÷¡œ‘ æª∫¥Ê
}

void myMouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		corner[0].x=x;
		corner[0].y=WIN_H-y;
		selected=true;
	}
	glutPostRedisplay();
}
void myPassiveMouse(int x,int y)
{
	corner[1].x=x;
	corner[1].y=WIN_H-y;
	glutPostRedisplay();
}

int main(int argc,char**argv)
{
	glutInit(&argc,argv);

	glutInitWindowSize(WIN_W,WIN_H);

	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);

	glutCreateWindow("DEMO");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,WIN_W,0.0,WIN_H);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glViewport(0.0,0.0,WIN_W,WIN_H);
	glutDisplayFunc(mydisplay);
	//glutMouseFunc(myMouse);
	//glutPassiveMotionFunc(myPassiveMouse);
	glutKeyboardFunc(mykeyboard);
	glutMainLoop();

}