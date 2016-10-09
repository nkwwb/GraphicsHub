#include "stdafx.h"
#include "DrawLib.h"
#include "editor.h"
#include <vector>

Point2d p[2];
Rectd rect;
bool select=false;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	DrawLib::drawLine2d(p[0],p[1],GlutEnvironmentInit::getForeGroundColor());
	glBegin(GL_LINE_LOOP);
	glVertex2d(rect.left,rect.bottom);
	glVertex2d(rect.right,rect.bottom);
	glVertex2d(rect.right,rect.top);
	glVertex2d(rect.left,rect.top);
	glEnd();
	glutSwapBuffers();
}
void keyboard(uchar key,int x,int y)
{
	if(key=='c')
	{
		DrawLib::clipSegment(p[0],p[1],rect);
		glutPostRedisplay();
	}
}

void mouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		select=true;
		p[0].x=x;p[0].y=REV(y);
		
	}
	else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
		select=false;
		p[1].x=x;p[1].y=REV(y);
		glutPostRedisplay();
	}
}

void move(int x,int y)
{
	if(select)
	{
		p[1].x=x;p[1].y=REV(y);
		glutPostRedisplay();
	}
}

int main(int argc, char**argv)
{
	glutInit(&argc,argv);
	p[0]=Point2d(0.0,0.0);p[1]=Point2d(0.0,0.0);
	rect=Rectd(160.0,480.0,120.0,360.0);
	GlutEnvironmentInit().GeneralInit(GLUT_RGB|GLUT_DOUBLE,GL_PROJECTION,display,keyboard,mouse,move);
	glutMainLoop();
}