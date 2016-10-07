
#pragma once

#include <GL\glut.h>
#include <GL\gl.h>

#ifndef WIN_W
#define WIN_W 640
#endif

#ifndef WIN_H
#define WIN_H 480
#endif

#ifndef null
#define null 0
#endif

typedef unsigned char uchar;
typedef unsigned int uint;

class Point{
public:
	GLint x;
	GLint y;
	Point();
	Point(GLint x0,GLint y0);
	bool operator==(const Point& p)const;
};

typedef Point Point2i;

class Color{
	
public:
	GLfloat r,g,b;
	//Color();
	Color(GLfloat r0,GLfloat g0,GLfloat b0);

};

class Size{
public:
	int width;
	int height;
public:
	Size(int w,int h);
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

	void GeneralInit(uint displayMode,GLenum matrixMode,\
		void (*displayfun)(),\
		void (*keyboardfun)(uchar key,int x,int y)=null,\
		void (*mousefun)(int button,int state,int x,int y)=null,\
		void (*mouseMovefun)(int x,int y)=null,\
		void (*mousePassiveMovefun)(int x,int y)=null,\
		Color3f fore=Color3f(0.0f,0.0f,0.0f),\
		Color4f back=Color4f(1.0f,1.0f,1.0f,0.0f),\
		char* winName="WINDOW",\
		Size winsize=Size(WIN_W,WIN_H));
		

};