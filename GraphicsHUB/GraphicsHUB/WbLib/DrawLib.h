#pragma once
//using namespace std;
#include <vector>

#include "stdafx.h"



class DrawLib{
private:
	
public:
	static void drawPoints2i(GLint x,GLint y,Color3f c);

	static void drawPoints2d(GLdouble x,GLdouble y,Color3f c);
	
	static void drawLine2i(GLint x1,GLint y1,GLint x2,GLint y2,Color c);

	static void drawLine2i(Point2i p1,Point2i p2,Color3f c);

	static void drawLine2d(GLdouble x1,GLdouble y1,GLdouble x2,GLdouble y2,Color c);

	static void drawLine2d(Point2d p1,Point2d p2,Color3f c);
	
	static void drawLineStrip2i(std::vector<Point2i> PointsArray,Color c,bool closed=false);

	static void drawFunction(double (*fun)(double),double xlow,double xhigh,double ylow,double yhigh,double inc);

	static void drawCheckerBoard(int size,Color3f c1,Color3f c2,Point2i start=Point2i(0,0));

	

};

