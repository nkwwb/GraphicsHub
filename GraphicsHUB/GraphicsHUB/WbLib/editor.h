#pragma once

#include "stdafx.h"

#include <vector>
 
class Editor{

	void keyBoardEvents(uchar key,int x,int y);

	void MouseClick(int button, int state,int x,int y);

	void MouseMove(int x,int y);
};