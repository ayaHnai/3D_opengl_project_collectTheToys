//header

#pragma warning(disable:4996)
#include<GLFW/glfw3.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>
#include "imageloader.h"
#include<iostream>
#include <stdlib.h>
#include "text3d.h"

using namespace std;


GLuint model[10];    //model[0]-->elephant    /  model[1]-->teddy / 2:box /3:yoyo/ 4:teddy
int ite = 0,noOfCollected=0;
float angle, _angle = -30.0f, win_scale=4;
GLuint _textureId; //The id of the texture
float y = 40.0, x = 50.0,     y2 = 50.0, x2 = -50.0,    xbox = 0.0, box_angle = 16.0,    y3 = 20, x3 = 20, y4 = -20, x4 = -10;
const char* STRS[1] = { "gOoOd :D"};

void draw();
float randam(float xx, float yy);
GLuint loadTexture(Image* image);
void cleanup();	


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void loadObj(char *fname)
{
	FILE *fp;
	int read;
	GLfloat x, y, z;
	char ch;
	model[ite] = glGenLists(1);

	fp = fopen(fname, "r");
	//fp = fopen_s(&fp, "mba1.obj", "rt");

	if (!fp)
	{
		printf("can't open file %s\n", fname);
		return;
	}
	if(ite==1)glPointSize(2.0);
	else glPointSize(2.0);
	glNewList(model[ite], GL_COMPILE);
	{
		glPushMatrix();
		glBegin(GL_POINTS);
		while (!(feof(fp)))
		{
			read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
			if (read == 4 && ch == 'v')
			{
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
	glPopMatrix();
	glEndList();
	ite++;
	fclose(fp);
}




void display(void)
{
	glClearColor(0.4, 0.3, 40, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	draw();
	glutSwapBuffers(); //swap the buffers

}

void draw()
{
	
	//Add directed light
	GLfloat lightColor1[] = { 0.5f, 0.2f, 0.7f, 1.0f }; //Color (0.5, 0.2, 0.2)
														//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = { -1.0f, 0.5f, 0.5f, 0.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 1.0f, -6.0f);


	glDisable(GL_TEXTURE_2D);
	angle = angle + 0.1;
	if (angle > 360)angle = angle - 360;

	y = y - 0.04f;
	y2 = y2 - 0.03f;
	y3 -= 0.02f;
	y4 -= 0.015f;
	if (y < -50)
	{x = randam(x, y); y = 50;}
	if (y2 < -50)
	{x2 = randam(x2, y2); y2 = 50;}
	if (y3 < -50)
	{x3 = randam(x3, y3); y3 = 50; }
	if (y4 < -50)
	{x4 = randam(x4, y4); y4 = 50; }

	
	glPushMatrix();
	glTranslatef(x, y, -50);
	glColor3f(0.9, 0.2, 0.2);
	glScalef(0.2, 0.2, 0.2);
	glRotatef(angle, 0, 1, 1);
	glCallList(model[1]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x2, y2, -50);
	glColor3f(0.2, 0.9, 0.3);
	glScalef(0.011, 0.011, 0.011);
	glRotatef(angle, 1, 1, 0);
	glCallList(model[0]);
	glPopMatrix();
	//
	//box
	glPushMatrix();
	glTranslatef(xbox, -20, -50);
	glColor3f(0.3, 0.2, 0.5);
	glScalef(5, 5, 5);
	glRotatef(box_angle, 0, 1, 0);
	glCallList(model[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x3, y3, -50);
	glColor3f(0.9, 0.4, 0.1);
	glScalef(5, 5, 5);
	glRotatef(angle, 1, 1, 0);
	glCallList(model[3]);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(x4, y4, -50);
	glColor3f(0.8, 0.7, 0.1);
	glScalef(.2, .2, .2);
	glRotatef(angle, 1, 1, 0);
	glCallList(model[1]);
	glPopMatrix();


	glPushMatrix();
	if ((x2<(xbox + 10) && x2>(xbox - 10 )&& y2 < -30) || (x<(xbox + 10) && x>(xbox - 10) && y < -30) 
		|| (x3<(xbox + 10) && x3>(xbox - 10) && y3 < -30) || (x4<(xbox + 10) && x4>(xbox - 10) && y4 < -30))
	{
			glColor3f(0.3f, 1.0f, 0.3f);
			glScalef(win_scale, win_scale, win_scale);
			glTranslatef(xbox, -8, -30.0f);
			t3dDraw3D(STRS[0], 0, 0, 0.2f);
	}
	
	

	glPopMatrix();
	
}

float randam(float xx, float yy)
{
		yy = 50;
		xx = rand() % 100;
		xx = xx / 100.0;
		float yr = rand() % 100;
		yr = yr / 100.0;
		xx = (xx - yr) * 60;
		return xx;
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glShadeModel(GL_SMOOTH);
	t3dInit();
	
}

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		cleanup();
		exit(0);
		break;
	case '\r'://enter key
		cout << "1";
		break;
	}
}


void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		xbox -= 5;
		if (xbox < -50)xbox = 50;
		break;
	case GLUT_KEY_RIGHT:
		xbox += 5;
		if (xbox > 50)xbox = -50;
		break;
	case GLUT_KEY_UP:
		box_angle += 1.0;
		break;
	case GLUT_KEY_DOWN:
		box_angle -= 1.0;
		break;
	}
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
											 //Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
						  //as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}




void cleanup() {
	t3dCleanup();
}


void update(int value) {
	_angle += 1.5f;
	if (_angle > 360) {
		_angle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 450);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("Collect THe TOoys");

	initRendering();
	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(SpecialKeys);

	

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	loadObj("data/elepham.obj");//replace porsche.obj with radar.obj or any other .obj to display it
	loadObj("data/teddy.obj");
	loadObj("data/box.obj");
	loadObj("data/aya.obj");
	loadObj("data/porsche.obj");
	


	glutMainLoop();
	return 0;
}
