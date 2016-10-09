#include "stdafx.h"

GLfloat GlutEnvironmentInit::foreground_r,GlutEnvironmentInit::foreground_g,\
	GlutEnvironmentInit::foreground_b;

GLfloat GlutEnvironmentInit::background_r,GlutEnvironmentInit::background_g,\
	GlutEnvironmentInit::background_b,GlutEnvironmentInit::Alpha;
	 
GLint GlutEnvironmentInit::WIN_WIDTH,GlutEnvironmentInit::WIN_HEIGHT;

//template<typename T> Point<T>::Point(){}
//
//template<typename T> Point<T>::Point(T x0,T y0)
//{
//	x=x0;
//	y=y0;
//}
//
//template<typename T> bool Point<T>::operator==(const Point<T>& p)const
//{
//	return x==p.x && y==p.y;
//}

Color::Color(GLfloat r0,GLfloat g0,GLfloat b0)
{
	r=r0;
	g=g0;
	b=b0;
}
Color4f::Color4f(GLfloat r0,GLfloat g0,GLfloat b0,GLfloat alpha):Color(r0,g0,b0)
{
	Alpha=alpha;
}

//template<typename T> Rect<T>::Rect(T l,T r,T b,T t):left(l),right(r),bottom(b),top(t){}

Size::Size(int w,int h)
{
	width=w;
	height=h;
}

Color3f GlutEnvironmentInit::getForeGroundColor()
{
	return Color3f(foreground_r,foreground_g,foreground_b);
}

Color4f GlutEnvironmentInit::getBackGroundColor()
{
	return Color4f(background_r,background_g,background_b,Alpha);
}

GLint GlutEnvironmentInit::getWinWidth()
{
	return WIN_WIDTH;
}

GLint GlutEnvironmentInit::getWinHeight()
{
	return WIN_HEIGHT;
}

void GlutEnvironmentInit::setBackGroundColor(GLfloat r,GLfloat g,GLfloat b,GLfloat alpha)
{
	background_r=r;
	background_g=g;
	background_b=b;
	Alpha=alpha;
}

void GlutEnvironmentInit::setForeGroundColor(GLfloat r,GLfloat g,GLfloat b)
{
	foreground_r=r;
	foreground_g=g;
	foreground_b=b;

}
void GlutEnvironmentInit::setWindowSize(int width,int height)
{
	WIN_WIDTH=width;
	WIN_HEIGHT=height;
}

void GlutEnvironmentInit::setWindow(GLenum matrixmode,GLdouble left,GLdouble right,GLdouble bottom,GLdouble top)
{
	glMatrixMode(matrixmode);
	glLoadIdentity();
	gluOrtho2D(left,right,bottom,top);
}

void GlutEnvironmentInit::setViewport(GLint left,GLint right,GLint bottom,GLint top)
{
	glViewport(left,bottom,right-left,top-bottom);
}

/**
If call this function without calling set- API before,
it will use default parameters.
*/
void GlutEnvironmentInit::GeneralInit(uint displayMode,\
									  GLenum matrixMode,\
									  void (*displayfun)(),\
									  void (*keyboardfun)(uchar key,int x,int y),\
									  void (*mousefun)(int button,int state,int x,int y),\
									  void (*mouseMovefun)(int x,int y),\
									  void (*mousePassiveMovefun)(int x,int y),\
									  Color3f fore,\
									  Color4f back,\
									  char* winName,\
									  Size winsize\
									  )
{
	setWindowSize(winsize.width,winsize.height);
	setForeGroundColor(fore.r,fore.g,fore.b);
	setBackGroundColor(back.r,back.g,back.b);

	glutInitWindowSize(WIN_WIDTH,WIN_HEIGHT);
	glutInitDisplayMode(displayMode);
	glutCreateWindow(winName);
	glutDisplayFunc(displayfun);

	if(keyboardfun)
		glutKeyboardFunc(keyboardfun);
	if(mousefun)
		glutMouseFunc(mousefun);
	if(mouseMovefun)
		glutMotionFunc(mouseMovefun);
	if(mousePassiveMovefun)
		glutPassiveMotionFunc(mousePassiveMovefun);

	glClearColor(background_r,background_g,background_b,Alpha);
	glColor3f(foreground_r,foreground_g,foreground_b);

	/*glMatrixMode(matrixMode);
	glLoadIdentity();
	gluOrtho2D(0.0,WIN_WIDTH,0.0,WIN_HEIGHT);*/
	setWindow(matrixMode,0.0,WIN_WIDTH,0.0,WIN_HEIGHT);
}

