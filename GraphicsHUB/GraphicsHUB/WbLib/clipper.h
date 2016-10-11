#include "stdafx.h"

enum{LEFT,RIGHT,TOP,BOTTOM};

template<typename pointType,typename RectType>
class Cohend_suthland_Clipper{
private:
	static uchar getCode(pointType p,RectType rect);
	static void clipPoint(pointType& pmain,pointType poth,RectType rect,int clipsite); 

public:
	static bool clipSegment(pointType& p1,pointType& p2,RectType rect); 
};

template<typename pointType,typename RectType> 
uchar Cohend_suthland_Clipper<pointType,RectType>::getCode(pointType p,RectType rect)
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

/**
The annotated section is necessary when the control logic is 'if-if-if-if...' in cilpSement function.
In this situation,we should manually check whether delx or dely is zero to avoid the 'devide zero' error.

Assume such a situation, p1 is above and to the left of the window,with the code 'TTFF',and p2 is on the left boundary.
Under the control of 'if-if-if-if' logic, a point can be clipped 2 times at most in an iteration. After using the left boundary
to clip p1, p1 is moved to p2! However, it's code is not updated, so it can be clipped by top boundary continually,which leads
to the 'devide zero' error.

If we use 'if-elseif-elseif-elseif' logic, each point can be clipped once strictly in an iteration, avoiding the 'devide zero'
error. Therefore,the check below can be odmitted. 

*/

template<typename pointType,typename RectType> 
void Cohend_suthland_Clipper<pointType,RectType>::clipPoint(pointType& pmain,pointType poth,RectType rect,int clipsite)
{
	/*if(pmain.x==poth.x)
	{
		pmain.y=(clipsite==TOP)? rect.top : rect.bottom;
		return;
	}
	if(pmain.y==poth.y)
	{
		pmain.x=(clipsite==LEFT)? rect.left : rect.right;
		return;
	}*/

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
bool Cohend_suthland_Clipper<pointType,RectType>::clipSegment(pointType& p1,pointType& p2,RectType rect)
{
	do{
		pointType p1_(p1),p2_(p2);
		uchar c1=getCode(p1,rect);
		uchar c2=getCode(p2,rect);
		// accept:both points are FFFF,that is c1|c2==0
		if(!(c1 | c2))
			return 1;
		//reject:both points are above or below or to left or right of the winodw,==> c1 & c2 !=0
		//OR: points are in different zones,e.g.,TFFF and FTFF,that is: c1 & c2==0 and c1!=0 and c2!=0
		if((c1 & c2))
			return 0;

		if(c1 & 8) // left
			clipPoint(p1,p2,rect,LEFT);
		else if(c1 & 4)
			clipPoint(p1,p2,rect,TOP);
		else if(c1 & 2)
			clipPoint(p1,p2,rect,RIGHT);
		else if(c1 & 1)
			clipPoint(p1,p2,rect,BOTTOM);

		if(c2 & 8) // left
			clipPoint(p2,p1,rect,LEFT);
		else if(c2 & 4)
			clipPoint(p2,p1,rect,TOP);
		else if(c2 & 2)
			clipPoint(p2,p1,rect,RIGHT);
		else if(c2 & 1)
			clipPoint(p2,p1,rect,BOTTOM);

		// cross judge
		if(p1_.x<p2_.x && p1.x>p2.x || p1_.x>p2_.x && p1.x<p2.x)
		{
			p1.x=p1_.x,p1.y=p1_.y;
			p2.x=p2_.x,p2.y=p2_.y;
			return 0;
		}

	}while(1);

}

typedef Cohend_suthland_Clipper<Point2i,Recti> i_Cohend_Clipper;
typedef Cohend_suthland_Clipper<Point2d,Rectd> d_Cohend_Clipper;