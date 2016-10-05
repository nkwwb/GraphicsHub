
#pragma once

#include <GL\glut.h>
#include <GL\gl.h>

#ifndef WIN_W
#define WIN_W 640
#endif

#ifndef WIN_H
#define WIN_H 480
#endif

typedef unsigned char uchar;

class Point{
public:
	GLint x;
	GLint y;
	Point();
	Point(GLint x0,GLint y0);
};

typedef Point Point2i;

class Color{
	
public:
	GLfloat r,g,b;
	//Color();
	Color(GLfloat r0,GLfloat g0,GLfloat b0);

};

class Color4f:public Color{
public:
	GLfloat Alpha;
	Color4f(GLfloat r0,GLfloat g0,GLfloat b0,GLfloat alpha);
};

typedef Color Color3f;

class GlutEnvironmentInit{

	static GLfloat foreground_r,foreground_g,foreground_b;

	static GLfloat background_r,background_g,background_b,Alpha;

	static GLint WIN_WIDTH,WIN_HEIGHT;

	

public:
	static Color3f getForeGroundColor();
	static Color4f getBackGroundColor();
	static GLint getWinWidth();
	static GLint getWinHeight();
	static void setForeGroundColor(GLfloat r=0.0f,GLfloat g=0.0f,GLfloat b=0.0f);
	
	static void setBackGroundColor(GLfloat r=1.0f,GLfloat g=1.0f,GLfloat b=1.0f,GLfloat alpha=0.0f);

	static void setWindowSize(int width=WIN_W,int height=WIN_H);

	//GlutEnvironmentInit();

	void GeneralInit(void (*fun)(),char* winName="WINDOW");
	void AllInit(void (*fun)(),char* winName="WINDOW");
};