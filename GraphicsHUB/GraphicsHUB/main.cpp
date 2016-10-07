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
void draw2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	DrawLib::drawCheckerBoard(80,Color3f(0.2f,0.2f,0.2f),Color3f(0.8f,0.8f,0.8f));
	glFlush();
}
int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	GlutEnvironmentInit().GeneralInit(GLUT_RGB|GLUT_SINGLE,GL_PROJECTION,draw,0,0,0,0);
	glutMainLoop();
}