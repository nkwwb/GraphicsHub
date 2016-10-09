#pragma once
//using namespace std;
#include <vector>

#include "stdafx.h"

enum{LEFT,RIGHT,TOP,BOTTOM};

class DrawLib{
private:
	template<typename pointType,typename RectType> static uchar getCode(pointType p,RectType rect);
	template<typename pointType,typename RectType> static void clipPoint(pointType& pmain,pointType poth,RectType rect,int clipsite); 
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

	template<typename pointType,typename RectType> static bool clipSegment(pointType& p1,pointType& p2,RectType rect); 

};

template<typename pointType,typename RectType> 
uchar DrawLib::getCode(pointType p,RectType rect)
{
	uchar code=0;
	if(p.x<rect.left)
		code |= 8;
	if(p.y>rect.top)
		code |= 4;
	if(p.x>rect.right)
		code |= 2;
	if(p.y<rect.bottom)
		code |= 1;
	return code;
}
template<typename pointType,typename RectType> void DrawLib::clipPoint(pointType& pmain,pointType poth,RectType rect,int clipsite)
{
	if(pmain.x==poth.x)
	{
		pmain.y=(clipsite==TOP)? rect.top : rect.bottom;
		return;
	}
	if(pmain.y==poth.y)
	{
		pmain.x=(clipsite==LEFT)? rect.left : rect.right;
		return;
	}
	if(!strcmp(typeid(pmain.x).name(),"int"))
	{
		switch(clipsite)
		{
		case LEFT:
		case RIGHT:
			pmain.y-=(int)((pmain.y-poth.y)*1.0/(pmain.x-poth.x)*(pmain.x- (clipsite==LEFT?rect.left:rect.right)));
			pmain.x=(clipsite==LEFT?rect.left:rect.right);
			break;
		case TOP:
		case BOTTOM:
			pmain.x-=(int)((pmain.x-poth.x)*1.0/(pmain.y-poth.y)*(pmain.y- (clipsite==TOP?rect.top:rect.bottom)));
			pmain.y=(clipsite==TOP?rect.top:rect.bottom);
			break;
		}
	}
	else
	{
		switch(clipsite)
		{
		case LEFT:
		case RIGHT:
			pmain.y-=((pmain.y-poth.y)/(pmain.x-poth.x)*(pmain.x- (clipsite==LEFT?rect.left:rect.right)));
			pmain.x=(clipsite==LEFT?rect.left:rect.right);
			break;
		case TOP:
		case BOTTOM:
			pmain.x-=((pmain.x-poth.x)/(pmain.y-poth.y)*(pmain.y- (clipsite==TOP?rect.top:rect.bottom)));
			pmain.y=(clipsite==TOP?rect.top:rect.bottom);
			break;
		}
	}
}
template<typename pointType,typename RectType> 
bool DrawLib::clipSegment(pointType& p1,pointType& p2,RectType rect)
{
	do{
		uchar c1=getCode<pointType,RectType>(p1,rect);
		uchar c2=getCode<pointType,RectType>(p2,rect);
		// accept
		if(!(c1 | c2))
			return 1;
		//reject
		if(c1 & c2)
			return 0;

		if(c1 & 8) // left
			clipPoint(p1,p2,rect,LEFT);
		if(c1 & 4)
			clipPoint(p1,p2,rect,TOP);
		if(c1 & 2)
			clipPoint(p1,p2,rect,RIGHT);
		if(c1 & 1)
			clipPoint(p1,p2,rect,BOTTOM);

		if(c2 & 8) // left
			clipPoint(p2,p1,rect,LEFT);
		if(c2 & 4)
			clipPoint(p2,p1,rect,TOP);
		if(c2 & 2)
			clipPoint(p2,p1,rect,RIGHT);
		if(c2 & 1)
			clipPoint(p2,p1,rect,BOTTOM);

	}while(1);

}