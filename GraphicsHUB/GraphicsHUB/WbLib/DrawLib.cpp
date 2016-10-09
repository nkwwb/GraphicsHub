#include "DrawLib.h"
#include <iostream>
void DrawLib::drawPoints2i(GLint x,GLint y,Color3f c)
{
	glColor3f(c.r,c.g,c.b);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}
void DrawLib::drawPoints2d(GLdouble x,GLdouble y,Color3f c)
{
	glColor3f(c.r,c.g,c.b);
	glBegin(GL_POINTS);
	glVertex2d(x,y);
	glEnd();
}
void DrawLib::drawLine2i(GLint x1,GLint y1,GLint x2,GLint y2,Color3f c)
{
	glColor3f(c.r,c.g,c.b);
	glBegin(GL_LINES);
		glVertex2i(x1,y1);
		glVertex2i(x2,y2);
	glEnd();
}

void DrawLib::drawLine2i(Point2i p1,Point2i p2,Color3f c)
{
	glColor3f(c.r,c.g,c.b);
	glBegin(GL_LINES);
		glVertex2i(p1.x,p1.y);
		glVertex2i(p2.x,p2.y);
	glEnd();
}

void DrawLib::drawLine2d(GLdouble x1,GLdouble y1,GLdouble x2,GLdouble y2,Color c)
{
	glColor3f(c.r,c.g,c.b);
	glBegin(GL_LINES);
		glVertex2d(x1,y1);
		glVertex2d(x2,y2);
	glEnd();
}

void DrawLib::drawLine2d(Point2d p1,Point2d p2,Color3f c)
{
	glColor3f(c.r,c.g,c.b);
	glBegin(GL_LINES);
		glVertex2d(p1.x,p1.y);
		glVertex2d(p2.x,p2.y);
	glEnd();
}

void DrawLib::drawLineStrip2i(std::vector<Point2i> PointsArray,Color3f c,bool closed)
{
	glColor3f(c.r,c.g,c.b);
	if(!closed)
		glBegin(GL_LINE_STRIP);
	else 
		glBegin(GL_LINE_LOOP);
		
	for(std::vector<Point2i>::size_type i=0;i<PointsArray.size();i++)
		glVertex2i(PointsArray[i].x,PointsArray[i].y);
	glEnd();
}

void DrawLib::drawFunction(double (*fun)(double),double xlow,double xhigh,double ylow,double yhigh,double inc)
{
	int width=GlutEnvironmentInit::getWinWidth();
	int height=GlutEnvironmentInit::getWinHeight();
	Color3f foreColor=GlutEnvironmentInit::getForeGroundColor();
	double A=width/(xhigh-xlow);
	double B=-xlow*A;
	double C=height/(yhigh-ylow);
	double D=-ylow*C;

	for(double x=xlow;x<=xhigh;x+=inc)
	{
		drawPoints2d(A*x+B,C*fun(x)+D,foreColor);
	}
}

void DrawLib::drawCheckerBoard(int size,Color3f c1,Color3f c2,Point2i start)
{
	int win_sz=GlutEnvironmentInit::getWinHeight();
	if(win_sz!=GlutEnvironmentInit::getWinWidth())
	{
		std::cout<<"Error:Window is not a square.\n";
		return;
	}

	int num=win_sz/size;

	for(int i=0;i<num;i++)
	{
		for(int j=0;j<num;j++)
		{
			if((i+j)&1)
				glColor3f(c1.r,c1.g,c1.b);
			else glColor3f(c2.r,c2.g,c2.b);
			glRecti(i*size,j*size,(i+1)*size,(j+1)*size);
		}
	}
	
}

