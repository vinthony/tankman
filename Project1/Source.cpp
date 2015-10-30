
#include <iostream>

#include <GL\glut.h>
#include <GL\GLU.h>
#include <GL\GL.h>



using namespace std;
const int SCREEN_WIDTH = 800; //define the screen width
const int SCREEN_HEIGHT = 600; //define the screen height
const double fov = 60.0; //define the original fov
const float zNear = 0.1f; // define the z near location
const float zFar = 100.0f; // define the z far location
const float radisOfMap = 8.0; // define the half width of map
static float tankZ = 0; //the  z position of tank
static float rotateCount = 0; // part 2+3 rotate 
static float rotateCylinder = 0; // part 3 up down rotate
bool isWire = false; //  is wireframe mode 
bool isFPS = false; // is first view

struct vec3 {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};
vec3 camera = { 9.0, 6.0, 10.0 }; // the init camera position
vec3 center = { 0, 0, 0 }; // the camera look center
vec3 up = { 0, 1, 0 };  // the upward vector
void colorDeepGreen(){
	glColor3f(0.09, 0.63, 0.52);
}
void colorGreen(){
	glColor3f(0.18, 0.8, 0.44);
}
void colorOrange(){
	glColor3f(0.83,0.33,0);
}
void colorDeepOrange(){
	glColor3f(0.95, 0.61, 0.07);
}
void colorBackground(){
	glClearColor(0.13, 0.13, 0.13,1.0);
}
void drawTankPart1(){ 
	if (isWire){
		glBegin(GL_LINE_STRIP);
	}
	else{
		glBegin(GL_QUADS);
	}

	colorDeepGreen();
	glVertex3f(-1.0f, 0.0f, -1.0f); //bottom
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 3.0f);
	glVertex3f(1.0f, 0.0f, 3.0f);

	
	glVertex3f(-1.0f, 0.0f, -1.0f); //back
	glVertex3f(1.0f, 0.0f, -1.0f);
	colorGreen();
	glVertex3f(1.0f, 0.8f, -1.0f);
	glVertex3f(-1.0f, 0.8f, -1.0f);

	colorDeepGreen();
	glVertex3f(-1.0f, 0.0f, -1.0f); //left 
	glVertex3f(-1.0f, 0.0f, 3.0f);
	colorGreen();
	glVertex3f(-1.0f, 0.8f, 2.5f);
	glVertex3f(-1.0f, 0.8f, -1.0f);

	colorDeepGreen();
	glVertex3f(1.0f, 0.0f, -1.0f); //right
	glVertex3f(1.0f, 0.0f, 3.0f);
	colorGreen();
	glVertex3f(1.0f, 0.8f, 2.5f);
	glVertex3f(1.0f, 0.8f, -1.0f);

	colorGreen();
	glVertex3f(-1.0f, 0.8f, 2.5f); //front
	glVertex3f(1.0f, 0.8f, 2.5f);
	colorDeepGreen();
	glVertex3f(1.0f, 0.0f, 3.0f);
	glVertex3f(-1.0f, 0.0f, 3.0f);

	colorGreen();
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
	colorDeepOrange();
	glVertex3f(-1.0f, 0.8f, -1.0f); //bottom
	glVertex3f(1.0f, 0.8f, -1.0f);
	glVertex3f(1.0f, 0.8f, 1.0f);
	glVertex3f(-1.0f, 0.8f, 1.0f);

	glVertex3f(-1.0f, 0.8f, -1.0f); //back
	glVertex3f(1.0f, 0.8f, -1.0f);
	colorOrange();
	glVertex3f(0.5f, 1.8f, -0.5f);
	glVertex3f(-0.5f, 1.8f, -0.5f);

	colorDeepOrange();
	glVertex3f(-1.0f, 0.8f, -1.0f); //left 
	glVertex3f(-1.0f, 0.8f, 1.0f);
	colorOrange();
	glVertex3f(-0.5f, 1.8f, 1.0f);
	glVertex3f(-0.5f, 1.8f, -0.5f);

	colorDeepOrange();
	glVertex3f(1.0f, 0.8f, -1.0f); //right
	glVertex3f(1.0f, 0.8f, 1.0f);
	colorOrange();
	glVertex3f(0.5f, 1.8f, 1.0f);
	glVertex3f(0.5f, 1.8f, -0.5f);

	colorDeepOrange();
	glVertex3f(-1.0f, 0.8f, 1.0f); //front
	glVertex3f(1.0f, 0.8f, 1.0f);
	colorOrange();
	glVertex3f(0.5f, 1.8f, 1.0f);
	glVertex3f(-0.5f, 1.8f, 1.0f);


	glVertex3f(-0.5f, 1.8f, -0.5f); //top
	glVertex3f(0.5f, 1.8f, -0.5f);
	glVertex3f(0.5f, 1.8f, 1.0f);
	glVertex3f(-0.5f, 1.8f, 1.0f);

	glEnd();
}

void drawTankPart3(){
	glColor3f(0.61,0.35,0.71);
	GLUquadricObj* qobj = gluNewQuadric();
	if (isWire) gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 0.2f, 0.2f, 2.5f, 40, 40);
}
void drawGrid(){
	glBegin(GL_LINES);
	for (GLfloat i = -radisOfMap; i <= radisOfMap; i = i + 1){ // draw the map
		glVertex3f(radisOfMap, 0.0f, i);
		glVertex3f(-radisOfMap, 0.0f, i);
		glVertex3f(i, 0.0f, radisOfMap);
		glVertex3f(i, 0.0f, -radisOfMap);
	}
	glEnd();
}

void myDisplay(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	colorBackground();

	glMatrixMode(GL_MODELVIEW); // camera lookat
	glLoadIdentity();
	gluLookAt(camera.x, camera.y, camera.z, center.x, center.y, center.z, up.x, up.y, up.z);

	glBegin(GL_LINES);  //define a 0,1,0 vector to display the original point
	glColor3f(0.75f, 0.22f, 0.17f);
	glVertex3f(0.0, 10.0f, 0.0);
	glVertex3f(0.0, -10.0f, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnd();

	// draw grids
	glPushMatrix();
	drawGrid();
	glPopMatrix();

	//draw the tank part 1; and translate the tank
	glPushMatrix();
		glTranslatef(0, 0, tankZ);
		drawTankPart1();
	glPopMatrix();

	//draw the tank part 2; and translate the tank part1&2 ,rotate part 2
	//  trans * rotate * tans2 * tans1 * point
	glPushMatrix();
	glTranslatef(0 , 0, tankZ); //trans
	glRotatef(rotateCount, 0.0, 1.0, 0.0); //rotate
	glTranslatef(0, 0, -tankZ); //tran1
	glTranslatef(0, 0, tankZ); // tran2
	drawTankPart2(); //point
	glPopMatrix();

	
	//draw the tank part3, and translate the tank part1,2,3 ,rotate part2, rotate part3
	glPushMatrix();
	glTranslatef(0.0f, 1.2f, tankZ+1.0f);
	glRotatef(rotateCylinder, 1.0, 0.0, 0.0);
	glTranslatef(0.0f, -1.2f, -(tankZ+1.0f));

	glTranslatef(0, 1.2f, tankZ);
	glRotatef(rotateCount, 0.0, 1.0, 0.0); //rotate
	glTranslatef(0, -1.2f, -tankZ);
	glTranslatef(0, 1.2f, tankZ+1.0f);
	drawTankPart3();
	glPopMatrix();
	
	glutSwapBuffers();

}

void myKeyboard(unsigned char key, int x, int y){
	switch (key)
	{
	case 'f':
		if (tankZ < radisOfMap - 3.0f ){ //border injection
			tankZ += 1.0;
		}
		if (isFPS){ //set first-view camera position;
			camera.x = 0.0;
			camera.y = 3.0;
			camera.z = tankZ;
			center.x = 0.0;
			center.y = 2.0;
			center.z = tankZ + 3.0;
		}
		break;
	case 'b':
		if (tankZ > - ( radisOfMap-1.0f )){ 
			tankZ -= 1.0;
		}
		if (isFPS){
			camera.x = 0.0;
			camera.y = 3.0;
			camera.z = tankZ;
			center.x = 0.0;
			center.y = 2.0;
			center.z = tankZ + 3.0;
		}
		break;
	case 'r':
		tankZ = 0.0;
		rotateCount = 0.0;
		rotateCylinder = 0.0;
		break;
	case 'w':
		isWire = !isWire;
		break;
	case 't':
		rotateCount += 10.0;
		break;
	case 'u':
		if (rotateCylinder > -20.0){
			rotateCylinder -= 5.0;
		}
		break;
	case 'd':
		if (rotateCylinder < 10.0){
			rotateCylinder += 5.0;
		}
		break;
	case 'h':
		camera.y -= 1.0;
		break;
	case 'j':
		camera.y += 1.0;
		break;
	case 'k':
		camera.z -= 1.0;
		break;
	case 'l':
		camera.z += 1.0f;
		break;
	case 'o':
		camera.x -= 1.0f;
		break;
	case 'p':
		camera.x += 1.0f;
		break;
	case 'm':
		isFPS = !isFPS;
		if (isFPS)
		{
			camera.x = 0.0;
			camera.y = 3.0;
			camera.z = tankZ;
			center.x = 0.0;
			center.y = 2.0;
			center.z = tankZ + 3.0;
		}
		else{
			camera = { 20.0, 10.0, 5.0 }; // the init camera position
			center = { 0, 0, 0 }; // the camera look center
			up = { 0, 1, 0 };  // the upward vector
		}
			break;
		default:
			break;
	}
	printf("%f,%f,%f\n", camera.x, camera.y, camera.z);
	glutPostRedisplay();
}
void myReshape(int width, int height){
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //change the perspective;
	gluPerspective(fov, (GLfloat)width / (GLfloat)height, zNear, zFar);
}

void myAnimation(void){

}

void init(void)

{
	// whole init
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION); // set the perspective function
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