#pragma once
//using namespace std;
#include <vector>

#include "stdafx.h"


class DrawLib{
public:
	static void drawPoints2i(GLint x,GLint y,Color3f c);

	static void drawPoints2d(GLdouble x,GLdouble y,Color3f c);
	
	static void drawLine2i(GLint x1,GLint y1,GLint x2,GLint y2,Color c);

	static void drawLine2i(Point2i p1,Point2i p2,Color3f c);
	
	static void drawLineStrip2i(std::vector<Point> PointsArray,Color c,bool closed=false);

	static void drawFunction(double (*fun)(double),double xlow,double xhigh,double ylow,double yhigh,double inc);

	static void drawCheckerBoard(int size,Color3f c1,Color3f c2,Point2i start=Point2i(0,0));

};
