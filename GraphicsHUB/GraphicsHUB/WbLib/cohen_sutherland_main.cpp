#include "stdafx.h"
#include "DrawLib.h"
#include "clipper.h"
#include "editor.h"
#include <vector>

Point2i p[2];
Recti RectK;
bool select=false;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	DrawLib::drawLine2i(p[0],p[1],GlutEnvironmentInit::getForeGroundColor());
	glBegin(GL_LINE_LOOP);
	glVertex2i(RectK.left,RectK.bottom);
	glVertex2i(RectK.right,RectK.bottom);
	glVertex2i(RectK.right,RectK.top);
	glVertex2i(RectK.left,RectK.top);
	glEnd();
	glutSwapBuffers();
}
void keyboard(uchar key,int x,int y)
{
	if(key=='c')
	{
		if(i_Cohend_Clipper::clipSegment(p[0],p[1],RectK))
			glutPostRedisplay();
		else {

			p[0]=Point2i(0,0);p[1]=Point2i(0.0,0.0);
			glutPostRedisplay();
		}
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
	p[0]=Point2i(0,0);p[1]=Point2i(0,0);
	RectK=Recti(160,480,120,360);
	GlutEnvironmentInit().GeneralInit(GLUT_RGB|GLUT_DOUBLE,GL_PROJECTION,display,keyboard,mouse,move);
	glutMainLoop();
}