#include "stdafx.h"
#include "DrawLib.h"
#include "editor.h"




int main(int argc,char**argv)
{
	glutInit(&argc,argv);

	

	GlutEnvironmentInit().GeneralInit(GLUT_RGB|GLUT_DOUBLE,\
		GL_PROJECTION,\
		Editor::Display,\
		Editor::keyBoardEvents,\
		Editor::MouseClick,\
		Editor::MouseMove,\
		Editor::MousePassiveMove,\
		Color3f(1.0f,1.0f,1.0f),\
		Color4f(0.0f,0.0f,0.0f,0.0f));

	//glutInitWindowSize(WIN_W,WIN_H);

	//glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);

	/*glutCreateWindow("DEMO");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,WIN_W,0.0,WIN_H);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	
	glViewport(0.0,0.0,WIN_W,WIN_H);
	glutDisplayFunc(mydisplay);
	glutMouseFunc(myMouse);
	glutPassiveMotionFunc(myPassiveMouse);
	glutKeyboardFunc(mykeyboard);*/
	glutMainLoop();

}