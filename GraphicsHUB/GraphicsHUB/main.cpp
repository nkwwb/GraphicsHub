#include "WbLib/stdafx.h"
#include "WbLib/DrawLib.h"
#include <math.h>

#define PI 3.141592627

double fun(double x)
{
	return sin(x)/x;
}
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	double (*ptr)(double)=fun;
	DrawLib::drawFunction(ptr,-20.0,20.0,-1.0,1.0,1e-3);
	glFlush();
}
void drawfun_viewport()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//// world window
	//gluOrtho2D(-21.0,21.0,-1.1,1.1);
	GlutEnvironmentInit().setWindow(GL_PROJECTION,-21.0,21.0,-1.1,1.1);
	//default the whole window
	//glViewport(0,0,640,480);
	for(GLdouble x=-20.0;x<=20.0;x+=1e-3)
	{
		DrawLib::drawPoints2d(x,fun(x),GlutEnvironmentInit::getForeGroundColor());
	}
	glFlush();
}

void draw2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	DrawLib::drawCheckerBoard(80,Color3f(0.2f,0.2f,0.2f),Color3f(0.8f,0.8f,0.8f));
	glFlush();
}
int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	GlutEnvironmentInit().GeneralInit(GLUT_RGB|GLUT_SINGLE,GL_PROJECTION,drawfun_viewport,0,0,0,0);
	glutMainLoop();
}