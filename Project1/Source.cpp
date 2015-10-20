
#include <iostream>

#include <GL\glut.h>
#include <GL\GLU.h>
#include <GL\GL.h>



using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const double fov = 60.0;
const float zNear = 0.1f;
const float zFar = 100.0f;
const float radisOfMap = 8.0;
static float tankX = 0;
static float tankY = 0;

struct vec3 {
	GLdouble x;
	GLdouble y;
	GLdouble z;
};




void myDisplay(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	

	
	//grids
	glBegin(GL_LINES);
	
	for (GLfloat i = -radisOfMap; i <= radisOfMap; i = i + 1){ // draw the 
		glVertex3f(radisOfMap, 0.0f, i);
		glVertex3f(-radisOfMap, 0.0f, i);
		glVertex3f(i, 0.0f, radisOfMap);
		glVertex3f(i, 0.0f, -radisOfMap);
	}
	glEnd();


	glBegin(GL_QUADS);
	
	glColor3f(0.0, 0.7, 0.2);
	glVertex3f(-1.0f,0.0f,0.0f); //bottom
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 4.0f);
	glVertex3f(1.0f, 0.0f, 4.0f);

	glColor3f(0.0, 0.7, 0.2);
	glVertex3f(-1.0f, 0.0f, 0.0f); //back
	glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3f(0.0, 0.3, 0.0);
	glVertex3f(-1.0f, 0.8f, 0.0f);
	glVertex3f(1.0f, 0.8f, 0.0f);

	glColor3f(0.0, 0.0, 0.2);
	glVertex3f(-1.0f, 0.0f, 0.0f); //left 
	glVertex3f(-1.0f, 0.0f, 4.0f);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-1.0f, 0.8f, 3.5f);
	glVertex3f(-1.0f, 0.8f, 0.0f);

	glColor3f(0.0, 0.3, 0.0);
	glVertex3f(1.0f, 0.0f, 0.0f); //right
	glVertex3f(1.0f, 0.0f, 4.0f);
	glColor3f(0.0, 0.7, 0.2);
	glVertex3f(1.0f, 0.8f, 3.5f);
	glVertex3f(1.0f, 0.8f, 0.0f);

	glColor3f(0.0, 0.7, 0.2);
	glVertex3f(-1.0f, 0.8f, 3.5f); //front
	glVertex3f(1.0f, 0.8f, 3.5f);
	glColor3f(0.0, 0.3, 0.0);
	glVertex3f(1.0f, 0.0f, 4.0f);
	glVertex3f(-1.0f, 0.0f, 4.0f);
	
	glColor3f(0.0, 0.7, 0.2);
	glVertex3f(-1.0f, 0.8f, 0.0f); //top
	glVertex3f(1.0f, 0.8f, 0.0f);
	glVertex3f(1.0f, 0.8f, 3.5f);
	glVertex3f(-1.0f, 0.8f, 3.5f);

	glColor3f(1.0, 0.7, 0.2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-1.0f, 0.8f, 0.0f); //bottom
	glVertex3f(1.0f, 0.8f, 0.0f);
	glVertex3f(1.0f, 0.8f, 2.0f);
	glVertex3f(-1.0f, 0.8f,2.0f);

	glVertex3f(-1.0f, 0.8f, 0.0f); //back
	glVertex3f(1.0f, 0.8f, 0.0f);
	glVertex3f(0.5f, 1.8f, 0.5f);
	glVertex3f(-0.5f, 1.8f, 0.5f);

	glVertex3f(-1.0f, 0.8f, 0.0f); //left 
	glVertex3f(-1.0f, 0.8f, 2.0f);
	glVertex3f(-0.5f, 1.8f, 2.0f);
	glVertex3f(-0.5f, 1.8f, 0.5f);

	glVertex3f(1.0f, 0.8f, 0.0f); //right
	glVertex3f(1.0f, 0.8f, 2.0f);
	glVertex3f(0.5f, 1.8f, 2.0f);
	glVertex3f(0.5f, 1.8f, 0.5f);

	glVertex3f(-1.0f, 0.8f, 2.0f); //front
	glVertex3f(1.0f, 0.8f, 2.0f);
	glVertex3f(0.5f, 1.8f, 2.0f);
	glVertex3f(0.5f, 1.8f, 2.0f);


	glVertex3f(-0.5f, 1.8f, 0.5f); //top
	glVertex3f(0.5f, 1.8f, 0.5f);
	glVertex3f(0.5f,1.8f, 2.0f);
	glVertex3f(-0.5f, 1.8f, 2.0f);

	glEnd();
	//tanks
	GLUquadricObj* qobj = gluNewQuadric();
	gluCylinder(qobj, 0.2f, 0.2f,2.5f,32,32);


	glutSwapBuffers();

}

void myKeyboard(unsigned char key, int x, int y){
	switch (key)
	{
		case 'f':
			if (tankX < radisOfMap)
				tankX += 1.0;
			break;
		case 'b':
			if (tankX > - radisOfMap)
				tankX -= 1.0;
			break;
		case 'r':
			tankX = 0.0;
			tankY = 0.0;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}
void myReshape(int width, int height){

}

void myAnimation(void){

}

void init(void)

{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(fov,aspect,zNear,zFar);


	vec3 camera = {10,10,20};
	vec3 center = {0,0,0};
	vec3 up = {0,1,0};
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.x, camera.y, camera.z, center.x, center.y, center.z, up.x, up.y, up.z);

}



int main(int argc, char * argv[])

{



	glutInit(&argc, argv);



	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);



	glutInitWindowPosition(200, 200);



	glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);



	glutCreateWindow("TANK");


	init();


	glutDisplayFunc(&myDisplay);
	glutReshapeFunc(&myReshape);
	glutKeyboardFunc(&myKeyboard);
	glutIdleFunc(&myAnimation);
	glutMainLoop();



	return 0;



}