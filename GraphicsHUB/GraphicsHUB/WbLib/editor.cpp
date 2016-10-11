#include "editor.h"
#include "DrawLib.h"
#include "clipper.h"
// basic status
std::vector< std::vector<Point2i> > Editor::groupPoints;
int Editor::status=0;
int Editor::group_sz=0;
int Editor::npoints=0;
int Editor::group=-1,Editor::idx=-1;

// global variable

Point2i CP;
Point2i MoveSeed;
Point2i OriSeed;
bool selected=false;
bool move_selected=false;
bool initstate=true;
bool rect_selected=false;
Recti rect;
Point2i rect_start,rect_end;

#define DRAWRECT(rect) \
{ \
	std::vector<Point2i> parray;\
	parray.push_back(Point2i(rect.left,rect.bottom));\
	parray.push_back(Point2i(rect.right,rect.bottom));\
	parray.push_back(Point2i(rect.right,rect.top));\
	parray.push_back(Point2i(rect.left,rect.top));\
	DrawLib::drawLineStrip2i(parray,GlutEnvironmentInit::getForeGroundColor(),true);\
}


bool Editor::search(Point2i seed,int& group,int& idx)
{
	group=idx=-1;
	int w=GlutEnvironmentInit::getWinWidth(),h=GlutEnvironmentInit::getWinHeight();
	int Min=(int)(w*w+h*h);
	for(unsigned int i=0;i<groupPoints.size();i++)
	{
		for(unsigned int j=0;j<groupPoints[i].size();j++)
		{

			int x=groupPoints[i][j].x, y=groupPoints[i][j].y;
			if(abs(x-seed.x)<SEARCH_WIN && abs(y-seed.y)<SEARCH_WIN) // effective
			{
				if(DIST(seed,groupPoints[i][j])<Min)
				{
					Min=DIST(seed,groupPoints[i][j]);
					group=i;idx=j;
				}
			}
		}
	}
	if(group!=-1&&idx!=-1)
		return true;
	else 
		return false;
}

void Editor::Display()
{
	if(initstate)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
		initstate=false;
	}
	else
	{
		switch(status)
		{
		case LINE:
			if(selected)
			{
				glClear(GL_COLOR_BUFFER_BIT);
				for(unsigned int i=0;i<groupPoints.size()-1;i++)
					DrawLib::drawLineStrip2i(groupPoints[i],GlutEnvironmentInit::getForeGroundColor(),true);
				DrawLib::drawLineStrip2i(groupPoints[groupPoints.size()-1],GlutEnvironmentInit::getForeGroundColor());
				DrawLib::drawLine2i(groupPoints[group_sz-1][npoints-1],CP,GlutEnvironmentInit::getForeGroundColor());
				DRAWRECT(rect);
				glutSwapBuffers();
			}
			break;

		case RECT:
			if(rect_selected)
			{
				glClear(GL_COLOR_BUFFER_BIT);
				for(unsigned int i=0;i<groupPoints.size();i++)
					DrawLib::drawLineStrip2i(groupPoints[i],GlutEnvironmentInit::getForeGroundColor(),true);
				DRAWRECT(rect);
				glutSwapBuffers();
			}
			break;

		case DEL:
			glClear(GL_COLOR_BUFFER_BIT);
			for(unsigned int i=0;i<groupPoints.size();i++)
					DrawLib::drawLineStrip2i(groupPoints[i],GlutEnvironmentInit::getForeGroundColor(),true);
			DRAWRECT(rect);
			glutSwapBuffers();
			break;

		case MOVE:
			if(move_selected)
			{
				glClear(GL_COLOR_BUFFER_BIT);
				for(unsigned int i=0;i<group;i++)
					DrawLib::drawLineStrip2i(groupPoints[i],GlutEnvironmentInit::getForeGroundColor(),true);
				for(unsigned int i=group+1;i<group_sz;i++)
					DrawLib::drawLineStrip2i(groupPoints[i],GlutEnvironmentInit::getForeGroundColor(),true);
				groupPoints[group][idx].x=OriSeed.x+(CP.x-MoveSeed.x);
				groupPoints[group][idx].y=OriSeed.y+(CP.y-MoveSeed.y);
				DrawLib::drawLineStrip2i(groupPoints[group],GlutEnvironmentInit::getForeGroundColor(),true);
				DRAWRECT(rect);
				glutSwapBuffers();
			}
		}
	}
}

void Editor::keyBoardEvents(uchar key,int x,int y)
{
	switch(key)
	{
	case 'b':
		status=BASIC;
		break;
	case 'l':
		if(status!=LINE) // other status
			status=LINE; // status:draw a line
		else  // second press 'l',end of a group of points
		{
			if(group_sz>0)
			{
				
				//DrawLib::drawLine2i(groupPoints[group_sz-1][npoints-1],CP,GlutEnvironmentInit::getBackGroundColor());
				// the last closing edge
				//DrawLib::drawLine2i(groupPoints[group_sz-1][0],groupPoints[group_sz-1][npoints-1],GlutEnvironmentInit::getForeGroundColor());
				glClear(GL_COLOR_BUFFER_BIT);
				for(unsigned int i=0;i<groupPoints.size();i++)
					DrawLib::drawLineStrip2i(groupPoints[i],GlutEnvironmentInit::getForeGroundColor(),true);
				DRAWRECT(rect);
				npoints=0;
				status=BASIC; // return to basic status
				selected=false;
				glutSwapBuffers();
			}
		}
		break;
	case 'w':
		status=RECT;
		break;
	case 'd':
		status=DEL;
		break;
		
	case 'm':
		status=MOVE;
		break;

	case 'c':
		glClear(GL_COLOR_BUFFER_BIT);
		DRAWRECT(rect);
		for(unsigned int i=0;i<groupPoints.size();i++)
		{
			for(unsigned int j=0;j<groupPoints[i].size();j++)
			{
				Point2i p1(groupPoints[i][j]);
				Point2i p2(groupPoints[i][(j+1)%groupPoints[i].size()]);

				// red in, blue out
				if(i_Cohend_Clipper::clipSegment(p1,p2,rect))
				{
					DrawLib::drawLine2i(groupPoints[i][j],p1,Color3f(0.0f,0.0f,1.0f));
					DrawLib::drawLine2i(p1,p2,Color3f(1.0f,0.0f,0.0f));
					DrawLib::drawLine2i(p2,groupPoints[i][(j+1)%groupPoints[i].size()],Color3f(0.0f,0.0f,1.0f));
				}
				else
				{
					DrawLib::drawLine2i(groupPoints[i][j],p1,Color3f(0.0f,0.0f,1.0f));
					DrawLib::drawLine2i(p1,p2,Color3f(0.0f,0.0f,1.0f));
					DrawLib::drawLine2i(p2,groupPoints[i][(j+1)%groupPoints[i].size()],Color3f(0.0f,0.0f,1.0f));
				}
			}
		}
		
		glutSwapBuffers();
		break;

	case 'r':
		status=BASIC;// return to basic
		initstate=true;
		groupPoints.clear();
		group_sz=0;
		npoints=0;
		rect=Recti(0,0,0,0);
		glutPostRedisplay();
		break;

	case 'q':
		status=QUIT;
		glutDestroyWindow(glutGetWindow());
		exit(1);
		break;

	}
}

void Editor::MouseClick(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		switch(status)
		{
		case LINE:
			if(npoints==0)
			{
				groupPoints.push_back(std::vector<Point2i>());
				group_sz++;
				groupPoints[group_sz-1].push_back(Point2i(x,REV(y)));
				npoints++;
			}
			else
			{
				groupPoints[group_sz-1].push_back(Point2i(x,REV(y)));
				npoints++;
			}
			selected=true;
			glutPostRedisplay();// call the display function
			break;

		case RECT:
			rect_start=Point2i(x,REV(y));
			rect_selected=true;
			glutPostRedisplay();
			break;

		case DEL:
			
			if(search(Point2i(x,REV(y)),group,idx))
			{
				if(groupPoints[group].size()==1) // only one point
				{
					std::vector< std::vector<Point2i> >::iterator it=groupPoints.begin();
					for(int i=0;i<group;i++,it++);
					groupPoints.erase(it);
					group_sz--;
				}
				else
				{
					std::vector<Point2i>::iterator it=groupPoints[group].begin();
					for(int i=0;i<idx;i++,it++);
					groupPoints[group].erase(it);
					

				}
				glutPostRedisplay();
			}
			else 
				std::cout<<"The point you want to delete is not sure! Selete it again!\n";
			break;

		case MOVE:
			MoveSeed=Point2i(x,REV(y));
			if(search(Point2i(x,REV(y)),group,idx))
			{
				OriSeed=groupPoints[group][idx];
				move_selected=true;
			}
			else
			{
				// if a point is not selected, we must not allow to move!
				move_selected=false;
				std::cout<<"The point you want to move is not sure! Selete it again!\n";
			}
		}
	}
	else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
		if(status==MOVE)
			move_selected=false;
		else if(status==RECT)
			rect_selected=false;
	}
}

void Editor::MousePassiveMove(int x,int y)
{
	if(status==LINE)
	{
		CP=Point2i(x,REV(y));
		glutPostRedisplay();
	}
}

void Editor::MouseMove(int x,int y)
{
	// only when a point is selected can you drag it.
	if(status==MOVE&&move_selected)
	{
		CP=Point2i(x,REV(y));
		glutPostRedisplay();
	}
	else if(status==RECT&&rect_selected)
	{
		rect.left=rect_start.x<x?rect_start.x:x;
		rect.right=rect_start.x>x?rect_start.x:x;
		rect.top=rect_start.y>REV(y)?rect_start.y:REV(y);
		rect.bottom=rect_start.y<REV(y)?rect_start.y:REV(y);
		glutPostRedisplay();
	}
}