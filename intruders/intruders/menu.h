
//including windows, gl and glut for graphics
//stdio for buffering
#include <windows.h>
#include <gl\GL.h>
#include <glut.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;


//hold display list
GLuint displist; 

//two variables for window size
int w1;
int h1;
void reshape (GLsizei w, GLsizei h) {

		if (h <= 0)
    	h = 1;

	int aspectratio = w / h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(45.0f, aspectratio, 0.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();


	
//	glLoadIdentity();
//	glViewport(0,0,(GLsizei)w,(GLsizei)h);
//	gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
//	glMatrixMode(GL_MODELVIEW);
	

	//stop divide by 0 if window too small
	w1 = w;
	h1 = h;	
	if(h == 0)
	h = 1;
	if(w == 0)
	w = 1;
	float ratio = 1.0* w / h;

	}




//orthogonal projection
void orthogonalStart (void) {
	//switch to projection matrix
	glMatrixMode(GL_PROJECTION);

	//start projections
	glPushMatrix();
	
	//clear previous instructions
	glLoadIdentity();
	
	//change window size to variables defined
	gluOrtho2D(0, w1, 0, h1);

	//flip scene upside down
   // glScalef(1, -1, 1);

	//translate scene
  //  glTranslatef(0, -h1, 0);
	
	//switch back to model matrix
	glMatrixMode(GL_MODELVIEW);
}

void orthogonalEnd (void) {
	//Switch back to projection mode
	glMatrixMode(GL_PROJECTION);
	
	//Finish the calls above
	glPopMatrix();
	
	//Switch back to our model matrix
	glMatrixMode(GL_MODELVIEW);
}

void menudisplay (void) {

	//clearing draw buffer painting bkg red
	glClearColor (255.0,255.0,255.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();

	//calling function
	//orthogonalStart();

	//declare displist as display list 
	displist = glGenLists(1);
	
	//compile the new list
	glNewList(displist,GL_COMPILE); 
	
	//start projections
	glPushMatrix();

     
	for(int i=0; i<=4; i++){

		//draw a square
		//QUADSTRIP Improvement?
		glBegin(GL_QUADS);
		glColor3f(0,0,0);
		glVertex2f(100, 150);
		glColor3f(0,0,0);
		glVertex2f(100, 100);
		glColor3f(0,0,0);
		glVertex2f(400, 100);
		glColor3f(0,0,0);
		glVertex2f(400, 150);
	
		//end drawing
		glEnd();

		//end projections
		glPopMatrix();

	
		//translate start point
		glTranslatef(0, 75, 0);

	}




	//end the list
	glEndList(); 
	
	//call displist
	glCallList(displist);

	//calling function
	//orthogonalEnd();

	//move contents of back buffer to front buffer
	glutSwapBuffers();
	glLoadIdentity ();
	glFlush();
}

