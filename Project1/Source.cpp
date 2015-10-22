
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
static float rotateCount = 0;
static float rotateCylinder = 0;
static float prevPosition = 0.0f;
bool isWire = false;

struct vec3 {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};
vec3 camera = { 0.0, 5.0, 10.0 };
vec3 center = { 0, 0, 0 };
vec3 up = { 0, 1, 0 };
void drawTankPart1(){
	if (isWire){
		glBegin(GL_LINE_STRIP);
	}
	else{
		glBegin(GL_QUADS);
	}

	glColor3f(0.0, 0.7, 0.2);
	glVertex3f(-1.0f, 0.0f, -1.0f); //bottom
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 3.0f);
	glVertex3f(1.0f, 0.0f, 3.0f);

	glColor3f(0.0, 0.7, 0.2);
	glVertex3f(-1.0f, 0.0f, -1.0f); //back
	glVertex3f(1.0f, 0.0f, -1.0f);
	glColor3f(0.0, 0.3, 0.0);
	glVertex3f(-1.0f, 0.8f, -1.0f);
	glVertex3f(1.0f, 0.8f, -1.0f);

	glColor3f(0.0, 0.0, 0.2);
	glVertex3f(-1.0f, 0.0f, -1.0f); //left 
	glVertex3f(-1.0f, 0.0f, 3.0f);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-1.0f, 0.8f, 2.5f);
	glVertex3f(-1.0f, 0.8f, -1.0f);

	glColor3f(0.0, 0.3, 0.0);
	glVertex3f(1.0f, 0.0f, -1.0f); //right
	glVertex3f(1.0f, 0.0f, 3.0f);
	glColor3f(0.0, 0.7, 0.2);
	glVertex3f(1.0f, 0.8f, 2.5f);
	glVertex3f(1.0f, 0.8f, -1.0f);

	glColor3f(0.0, 0.7, 0.2);
	glVertex3f(-1.0f, 0.8f, 2.5f); //front
	glVertex3f(1.0f, 0.8f, 2.5f);
	glColor3f(0.0, 0.3, 0.0);
	glVertex3f(1.0f, 0.0f, 3.0f);
	glVertex3f(-1.0f, 0.0f, 3.0f);

	glColor3f(0.0, 0.7, 0.2);
	glVertex3f(-1.0f, 0.8f, -1.0f); //top
	glVertex3f(1.0f, 0.8f, -1.0f);
	glVertex3f(1.0f, 0.8f, 2.5f);
	glVertex3f(-1.0f, 0.8f, 2.5f);

	glColor3f(1.0, 0.7, 0.2);
	glEnd();
}
void drawTankPart2(){
	if (isWire){
		glBegin(GL_LINE_STRIP);
	}
	else{
		glBegin(GL_QUADS);
	}
	glVertex3f(-1.0f, 0.8f, -1.0f); //bottom
	glVertex3f(1.0f, 0.8f, -1.0f);
	glVertex3f(1.0f, 0.8f, 1.0f);
	glVertex3f(-1.0f, 0.8f, 1.0f);

	glVertex3f(-1.0f, 0.8f, -1.0f); //back
	glVertex3f(1.0f, 0.8f, -1.0f);
	glVertex3f(0.5f, 1.8f, -0.5f);
	glVertex3f(-0.5f, 1.8f, -0.5f);

	glVertex3f(-1.0f, 0.8f, -1.0f); //left 
	glVertex3f(-1.0f, 0.8f, 1.0f);
	glVertex3f(-0.5f, 1.8f, 1.0f);
	glVertex3f(-0.5f, 1.8f, -0.5f);

	glVertex3f(1.0f, 0.8f, -1.0f); //right
	glVertex3f(1.0f, 0.8f, 1.0f);
	glVertex3f(0.5f, 1.8f, 1.0f);
	glVertex3f(0.5f, 1.8f, -0.5f);

	glVertex3f(-1.0f, 0.8f, 1.0f); //front
	glVertex3f(1.0f, 0.8f, 1.0f);
	glVertex3f(0.5f, 1.8f, 1.0f);
	glVertex3f(-0.5f, 1.8f, 1.0f);


	glVertex3f(-0.5f, 1.8f, -0.5f); //top
	glVertex3f(0.5f, 1.8f, -0.5f);
	glVertex3f(0.5f, 1.8f, 1.0f);
	glVertex3f(-0.5f, 1.8f, 1.0f);

	glEnd();
}

void drawTankPart3(){
	GLUquadricObj* qobj = gluNewQuadric();
	if (isWire) gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 0.2f, 0.2f, 2.5f, 4, 4);
}
void drawGrid(){
	glBegin(GL_LINES);
	for (GLfloat i = -radisOfMap; i <= radisOfMap; i = i + 1){ // draw the 
		glVertex3f(radisOfMap, 0.0f, i);
		glVertex3f(-radisOfMap, 0.0f, i);
		glVertex3f(i, 0.0f, radisOfMap);
		glVertex3f(i, 0.0f, -radisOfMap);
	}
	glEnd();
}

void myDisplay(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.x, camera.y, camera.z, center.x, center.y, center.z, up.x, up.y, up.z);

	glBegin(GL_LINES);
	glVertex3f(0.0, 10.0f, 0.0);
	glVertex3f(0.0, -10.0f, 0.0);

	glEnd();
	//grids
	glPushMatrix();
	drawGrid();
	glPopMatrix();

	
	glPushMatrix();
		glTranslatef(0, 0, tankX);
		drawTankPart1();
	glPopMatrix();
	


	glPushMatrix();
	glTranslatef(0 , 0, tankX);
	glRotatef(rotateCount, 0.0, 1.0, 0.0); //rotate
	glTranslatef(0, 0, -tankX);
	glTranslatef(0, 0, tankX);
	drawTankPart2();
	glPopMatrix();

	
	glPushMatrix();
	/*
	glTranslatef(0.0f, 1.2f, tankX+1.5f);
	glRotatef(rotateCylinder, 1.0, 0.0, 0.0);
	glTranslatef(0.0f, -1.2f, -(tankX+1.5f));
	*/

	glTranslatef(0, 1.5f, tankX+1.5f);
	glRotatef(rotateCount, 0.0, 1.0, 0.0); //rotate
	glTranslatef(0, -1.5f, -(tankX+1.5f));
	glTranslatef(0, 1.5f, tankX+1.5f);
	drawTankPart3();
	glPopMatrix();
	
	glutSwapBuffers();

}

void myKeyboard(unsigned char key, int x, int y){
	switch (key)
	{
		case 'f':
			if (tankX < radisOfMap){
				prevPosition = tankX;
				tankX += 1.0;
			}
			break;
		case 'b':
			if (tankX > -radisOfMap){
				prevPosition = tankX;
				tankX -= 1.0;
			}
			break;
		case 'r':
			tankX = 0.0;
			tankY = 0.0;
			rotateCount = 0.0;
			rotateCylinder = 0.0;
			prevPosition = 0.0;
			break;
		case 'w':
			isWire = !isWire;
			break;
		case 't':
			rotateCount += 10.0;
			break;
		case 'u':
			rotateCylinder -= 10.0;
			break;
		case 'd':
			rotateCylinder += 10.0;
			break;
		case 'h':
			camera.x += 1.0;
			break;
		case 'j':
			camera.y += 1.0;
			break;
		case 'k':
			camera.z += 1.0;
			break;
		case 'l':
			camera.z -= 1.0f;
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
	// whole init
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(fov,aspect,zNear,zFar);


	
	

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