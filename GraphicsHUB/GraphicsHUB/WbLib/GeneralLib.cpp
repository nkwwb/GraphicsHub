#include "stdafx.h"

GLfloat GlutEnvironmentInit::foreground_r=0.0f,GlutEnvironmentInit::foreground_g=0.0f,\
	GlutEnvironmentInit::foreground_b=0.0f;

GLfloat GlutEnvironmentInit::background_r=1.0f,GlutEnvironmentInit::background_g=1.0f,\
	GlutEnvironmentInit::background_b=1.0f,GlutEnvironmentInit::Alpha=0.0f;
	 
GLint GlutEnvironmentInit::WIN_WIDTH=WIN_W,GlutEnvironmentInit::WIN_HEIGHT=WIN_H;

Point::Point(){}

Point::Point(GLint x0,GLint y0)
{
	x=x0;
	y=y0;
}

Color::Color(GLfloat r0,GLfloat g0,GLfloat b0)
{
	r=r0;
	g=g0;
	b=b0;
}
Color4f::Color4f(GLfloat r0,GLfloat g0,GLfloat b0,GLfloat alpha):Color(r0,g0,b0)
{
	Alpha=alpha;
}

Color3f GlutEnvironmentInit::getForeGroundColor()
{
	return Color3f(foreground_r,foreground_g,foreground_b);
}

Color4f GlutEnvironmentInit::getBackGroundColor()
{
	return Color4f(background_r,background_g,background_b,Alpha);
}

GLint GlutEnvironmentInit::getWinWidth()
{
	return WIN_WIDTH;
}

GLint GlutEnvironmentInit::getWinHeight()
{
	return WIN_HEIGHT;
}

void GlutEnvironmentInit::setBackGroundColor(GLfloat r,GLfloat g,GLfloat b,GLfloat alpha)
{
	background_r=r;
	background_g=g;
	background_b=b;
	Alpha=alpha;
}

void GlutEnvironmentInit::setForeGroundColor(GLfloat r,GLfloat g,GLfloat b)
{
	foreground_r=r;
	foreground_g=g;
	foreground_b=b;

}
void GlutEnvironmentInit::setWindowSize(int width,int height)
{
	WIN_WIDTH=width;
	WIN_HEIGHT=height;
}

/**
If call this function without calling set- API before,
it will use default parameters.
*/
void GlutEnvironmentInit::GeneralInit(void (*fun)(),char* winName)
{
	
	glutInitWindowSize(WIN_WIDTH,WIN_HEIGHT);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow(winName);
	glutDisplayFunc(fun);
	glClearColor(background_r,background_g,background_b,Alpha);
	glColor3f(foreground_r,foreground_g,foreground_b);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,WIN_WIDTH,0.0,WIN_HEIGHT);

}

/**
Use default parameters to initialize glut environment.
*/
void GlutEnvironmentInit::AllInit(void (*fun)(),char* winName)
{
	setBackGroundColor();
	setForeGroundColor();
	setWindowSize();

	glutInitWindowSize(WIN_WIDTH,WIN_HEIGHT);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow(winName);
	glutDisplayFunc(fun);
	glClearColor(background_r,background_g,background_b,Alpha);
	glColor3f(foreground_r,foreground_g,foreground_b);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,WIN_WIDTH,0.0,WIN_HEIGHT);
}