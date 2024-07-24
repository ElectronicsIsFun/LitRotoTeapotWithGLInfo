// Program name: LitRotoTeaPotWithGLinfo.cpp
//
// Written By: Carlos Santiago Date: 11/01/00
//
// This program demonstrates a rotating Tea Pot. 
// It also demonstrates view transformations (glFrustum(),
// glRotatef(), glMatrixMode(), and gluLookAt()).
//
// To correct for QUADS drawn out of order, I enabled Z-Buffering using
// the following functions:
//
// glEnable(GL_DEPTH_TEST);
// glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// glutInitDisplayMode (GLUT_DEPTH | GLUT_SINGLE | GLUT_RGB);
//
// Double buffering is used for animationg the Tea Pot.
// glutSwapBuffers() is used for page flipping GLUT_DOUBLE enables double buffering
// in glutInitDisplayMode().
//
// July 29, 2002 Added support to display OpenGL VENDOR, VERSION, RENDERER, and EXTENSIONS
//               Note: glGetString() must be called after the Window is created.
//
// December 4, 2002 renamed source from LitRotoTeaPot.cpp to LitRotoTeaPotWithGLinfo.cpp
//
// March 11, 2007 Modified to run on MacBook Pro with OSX 10.4.8
//

// #include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

static GLfloat theta = 0;    //Initial angle of X rotation.
static GLfloat alpha = 0;    //Initial angle of Y rotation.

void init(void) 
{

	//Lighting variables
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
    
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_specular);

	//Enable color tracking
	//If color tracking is not enabled, the scene will be rendered in gray scale
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	//Turn on the lights
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST); //Enable Z-Buffering
	

}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //Point the camera


	
//Draw the room before the cube is rotated otherwise, it will also rotate.

	glBegin(GL_QUADS);
		// Draw a floor
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(-5.0, -2.0, -5.0);
		glVertex3f(5.0, -2.0, -5.0);
		glVertex3f(5.0, -2.0, 5.0);
		glVertex3f(-5.0, -2.0, 5.0);
		// Draw a Back Wall
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(5.0, -2.0, 5.0);
		glVertex3f(-5.0, -2.0, 5.0);
		glVertex3f(-5.0, 5.0, 5.0);
		glVertex3f(5.0, 5.0, 5.0);
		// Draw a Ceiling
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-5.0, 5.0, -5.0);
		glVertex3f(5.0, 5.0, -5.0);
		glVertex3f(5.0, 5.0, 5.0);
		glVertex3f(-5.0, 5.0, 5.0);
		// Draw a Right wall
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(5.0, -2.0, 5.0);
		glVertex3f(5.0, -2.0, -5.0);
		glVertex3f(5.0, 5.0, -5.0);
		glVertex3f(5.0, 5.0, 5.0);
		// Draw a Left wall
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(-5.0, -2.0, 5.0);
		glVertex3f(-5.0, 5.0, 5.0);
		glVertex3f(-5.0, 5.0, -5.0);
		glVertex3f(-5.0, -2.0, -5.0);
	glEnd();
	
	glRotatef(theta, 1.0, 0.0, 0.0);
	glRotatef(alpha, 0.0, 1.0, 0.0);
   

// Draw the Tea Pot here.
	
	glutSolidTeapot(1.0f);
	

	glFlush ();
	glutSwapBuffers(); //Flip the page
}

void RotateCube(void)
{
	theta+=3; // Increment X rotation angle
	alpha+=3; // Increment Y rotation angle

	if( theta > 360.0) theta -= 360.0;
    if( alpha > 360.0) alpha -= 360.0;

	glutPostRedisplay();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
 
}


void keyboard(unsigned char key, int x, int y)
{
	//Exit when the <ESC> key is pressed
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
   glutInitWindowSize (250, 250); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("RotoTeapot with GLinfo");

	//Display OpenGL VENDOR, VERSION, RENDERER, and EXTENSIONS 
	const GLubyte* versionData = glGetString( GL_VENDOR );
	cout << "Vendor: " << versionData << endl;
	
	versionData = glGetString( GL_VERSION );
	cout << "Version: " << versionData << endl;
	
	versionData = glGetString( GL_RENDERER );
	cout << "Renderer: " << versionData << endl;
	
	versionData = glGetString( GL_EXTENSIONS );
	cout << "Extensions: " << versionData << endl;

   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutIdleFunc(RotateCube);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
   return 0;
}
