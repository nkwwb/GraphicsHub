#pragma once

#include "stdafx.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>
#define SEARCH_WIN 10

#define MAX(a,b) a>b?a:b
#define MIN(a,b) a<b?a:b
#define REV(y) GlutEnvironmentInit::getWinHeight()-y

#define DIST(p,q) (p.x-q.x)*(p.x-q.x)+(p.y-q.y)*(p.y-q.y)

enum MODE{BASIC,LINE,DEL,MOVE,REF,QUIT};

class Editor{

	static std::vector< std::vector< Point2i > > groupPoints;
	static int status;

	static int group_sz;
	static int npoints;

	static int group,idx;

private:
	static bool search(Point2i seed,int& group,int& idx);

public:

	static void keyBoardEvents(uchar key,int x,int y);

	static void MouseClick(int button, int state,int x,int y);

	static void MouseMove(int x,int y);

	static void MousePassiveMove(int x,int y);

	static void Display();
};