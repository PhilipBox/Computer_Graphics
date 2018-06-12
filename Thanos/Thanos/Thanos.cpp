#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <WinUser.h>
#include <time.h>
#include <math.h>
#include <glut.h>

#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment (lib, "fmodex_vc.lib")

using namespace FMOD;

#pragma warning(disable:4996)

#define TURN 2.0

// MAZE map
// 0 : Floor
// 1 : Start floor 
// 2 : End floor
// 3 : Side wall
// 4~8 : Infinity Stone wall
int map[11][11] = {
{ 3,3,3,3,3,3,3,3,3,3,3 },		//1
{ 1,0,0,0,0,0,0,0,0,0,4 },		//2
{ 3,3,3,0,3,0,3,0,3,3,3 }	,	//3
{ 3,3,3,0,3,3,3,0,3,6,3 },		//4
{ 3,0,0,0,3,5,0,0,3,0,3 },		//5
{ 3,0,3,0,3,3,3,0,0,0,3 },		//6
{ 3,0,3,0,3,3,3,3,3,3,3 },		//7
{ 3,0,3,0,0,0,0,0,0,0,3 },		//8
{ 3,0,3,3,3,3,3,0,3,0,3 },		//9
{ 3,0,0,7,3,8,0,0,3,0,3 },		//10
{ 3,3,3,3,3,3,3,3,3,2,3 }		//11
};

int width = 800, height = 600;
int w, h, window;

bool music = true, start = true, stop = false;
static int Mx = 0, My = 0;

GLuint LOAD_TEXTURE(const char *);
GLuint sideWall, underFloor	;	// bmp file variable for Wall&Floor 
GLuint endFloor, startFloor;		// bmp file variable for start&end floor
GLuint STONE[5];					// bmp file variable for Infinity STONE wall
GLuint SV_img[5];					// bmp file variabel for Infinity STONE inventory
GLuint Complete_g;

float a = 0.0, b = 1.0;		 // to save a vertex3f value cu
float c = 0.0, d = 1.0;		// to save a vertex3f value  fl0

System* pSystem;
Sound* pSound;
Channel* pChannel;

void TextureLoad();
void PrintTimeRemaining();
bool stone_condition[6] = { false };

GLfloat angX = 0.0;
GLfloat angY = 0.0;
GLfloat tmp_ang = 0.0;
GLdouble X = 3.0;
GLdouble Y = 0.0;
GLdouble Z = 1.2;

void init()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.3, 0.3, 0.7);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(100.0, 1.0, 0.01, 100.0);
	float Ambient_light[] = { 2.0f, 2.0f, 2.0f, 2.0f };
	float Diffuse_light[] = { 2.5f, 2.5f, 2.5f, 2.5f };
	float Position_light[4][4] = {
	{ 7.0f, 50.0f, 0.0f, 1.0f } ,
	{ 0.0f, 55.0f, 0.0f, 0.0f },
	{ 0.0f, 50.0f, 7.0f, 0.0f },
	{ 0.0f, 50.0f, 0.0f, 7.0f }
	};

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse_light);

	for (int i = 0; i < 4; i++)
		glLightfv(GL_LIGHT0, GL_POSITION, Position_light[i]);

	glEnable(GL_LIGHT0);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void GIVE_ME()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, Complete_g);
	glColor3f(1.0, 1.0, 1.0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(0.05, 0.05);
	glTexCoord2f(1.0, 1.0); glVertex2f(0.2, 0.05);
	glTexCoord2f(1.0, 0.0); glVertex2f(0.2, 0.3);
	glTexCoord2f(0.0, 0.0); glVertex2f(0.05, 0.3);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

//	inventory : Stone View functions [  SV1() ~ SV5() ] 
void SV1()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, SV_img[0]);
	glColor3f(1.0, 1.0, 1.0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(0.8, 0.05);
	glTexCoord2f(1.0, 1.0); glVertex2f(0.9, 0.05);
	glTexCoord2f(1.0, 0.0); glVertex2f(0.9, 0.15);
	glTexCoord2f(0.0, 0.0); glVertex2f(0.8, 0.15);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void SV2()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, SV_img[1]);
	glColor3f(1.0, 1.0, 1.0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(0.65, 0.05);
	glTexCoord2f(1.0, 1.0); glVertex2f(0.75, 0.05);
	glTexCoord2f(1.0, 0.0); glVertex2f(0.75, 0.15);
	glTexCoord2f(0.0, 0.0); glVertex2f(0.65, 0.15);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void SV3()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, SV_img[2]);
	glColor3f(1.0, 1.0, 1.0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(0.5, 0.05);
	glTexCoord2f(1.0, 1.0); glVertex2f(0.6, 0.05);
	glTexCoord2f(1.0, 0.0); glVertex2f(0.6, 0.15);
	glTexCoord2f(0.0, 0.0); glVertex2f(0.5, 0.15);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void SV4()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, SV_img[3]);
	glColor3f(1.0, 1.0, 1.0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(0.35, 0.05);
	glTexCoord2f(1.0, 1.0); glVertex2f(0.45, 0.05);
	glTexCoord2f(1.0, 0.0); glVertex2f(0.45, 0.15);
	glTexCoord2f(0.0, 0.0); glVertex2f(0.35, 0.15);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void SV5()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, SV_img[4]);
	glColor3f(1.0, 1.0, 1.0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(0.2, 0.05);
	glTexCoord2f(1.0, 1.0); glVertex2f(0.3, 0.05);
	glTexCoord2f(1.0, 0.0); glVertex2f(0.3, 0.15);
	glTexCoord2f(0.0, 0.0); glVertex2f(0.2, 0.15);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

// inventory : When you got all Infinity stone, This image is appeared
void Complete()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, endFloor);
	glColor3f(1.0, 1.0, 1.0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(0.45, 0.2);
	glTexCoord2f(1.0, 1.0); glVertex2f(0.65, 0.2);
	glTexCoord2f(1.0, 0.0); glVertex2f(0.65, 0.5);
	glTexCoord2f(0.0, 0.0); glVertex2f(0.45, 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


// function for loading texture
void TextureLoad()
{
	startFloor = LOAD_TEXTURE("start0.bmp");					// 1 - start image 
	endFloor = LOAD_TEXTURE("end_floor.bmp");						// 2 - end image 
	underFloor = LOAD_TEXTURE("under_space.bmp");		// 0 - floor image

	sideWall = LOAD_TEXTURE("space.bmp");					// 3 - side wall

															// Infinity STONE Image load
	STONE[0] = LOAD_TEXTURE("yellow.bmp");
	STONE[1] = LOAD_TEXTURE("blue.bmp");;
	STONE[2] = LOAD_TEXTURE("red.bmp");
	STONE[3] = LOAD_TEXTURE("purple.bmp");;
	STONE[4] = LOAD_TEXTURE("green.bmp");

	// Infinity STONE for invengory Image load
	SV_img[0] = LOAD_TEXTURE("sv1.bmp");
	SV_img[1] = LOAD_TEXTURE("sv2.bmp");
	SV_img[2] = LOAD_TEXTURE("sv3.bmp");
	SV_img[3] = LOAD_TEXTURE("sv4.bmp");
	SV_img[4] = LOAD_TEXTURE("sv5.bmp");

	Complete_g = LOAD_TEXTURE("complete.bmp");
}

void MouseHandler(int x, int y)
{
	GLdouble dX = x - Mx;
	GLdouble dY = y - My;

	if (dX < 0)
	{
		angX -= TURN;
		if (angX > 360.0) angX -= 360.0;
		if (angX < 0) angX += 360.0;
	}
	else
	{
		angX += TURN;
		if (angX < 0.0) angX += 360.0;
		if (angX > 360.0) angX -= 360.0;
	}

	Mx = x;
	My = y;
	glutPostRedisplay();
}

void KeyboardHandler(unsigned char key, int x, int y)
{

	PrintTimeRemaining();
	for (int i = 0; i < 6; i++)
	{
		printf("%d ", stone_condition[i]);
	}
	printf("\n");

	if (key == 'w')
	{
		int x = -1 * (int)((X - (0.1*sin(angX*(3.14 / 180)))) / 0.8);
		int z = (int)((Z + (0.1*cos(angX*(3.14 / 180)))) / 0.8);

		//printf("x: %d z: %d map: %d\n", x, z, map[z][x]);
		//printf("X: %.2lf Z: %.2lf\n\n", X, Z);

		if (x >= 0 && x < 11 && z >= 0 && z < 11)
		{
			if (map[z][x] == 0 || map[z][x] == 1 || map[z][x] == 2)
				X -= 0.1*sin(angX*(3.14 / 180));
			if (map[z][x] == 0 || map[z][x] == 1 || map[z][x] == 2)
				Z += 0.1*cos(angX*(3.14 / 180));
		}
		else
		{
			X -= 0.1*sin(angX*(3.14 / 180));
			Z += 0.1*cos(angX*(3.14 / 180));
		}

		// Collection Condition of Infinity stone
		if (x == 9 && z == 1)
			stone_condition[0] = true;
		else if (x == 6 && z == 4)
			stone_condition[1] = true;
		else if (x == 9 && z == 4)
			stone_condition[2] = true;
		else if (x == 2 && z == 9)
			stone_condition[3] = true;
		else if (x == 6 && z == 9)
			stone_condition[4] = true;


		// For ending condition
		if ((stone_condition[0] == true) && (stone_condition[1] == true) && (stone_condition[2] == true) && (stone_condition[3] == true) && (stone_condition[4] == true)) {
			stone_condition[5] = true;
		}

		if (stone_condition[5] == true)
			printf("타노스에게 스톤을 돌려주자!\n");

		if ((x == 9 && z == 9) && stone_condition[5] == true) {
			if (MessageBox(NULL, L"타노스가 당신을 좋아합니다♥.", L"타노스의 인피니티 스톤찾기", MB_OK | MB_ICONEXCLAMATION) == IDOK)
				exit(1);
		}
	}

	if (key == 's')
	{
		int x = -1 * (int)((X + (0.1*sin(angX*(3.14 / 180)))) / 0.8);
		int z = (int)((Z - (0.1*cos(angX*(3.14 / 180)))) / 0.8);

		//printf("x: %d z: %d map: %d\n", x, z, map[z][x]);
		//printf("X: %.2lf Z: %.2lf\n\n", X, Z);

		if (x >= 0 && x < 11 && z >= 0 && z < 11)
		{
			if (map[z][x] == 0 || map[z][x] == 1 || map[z][x] == 2)
				X += 0.1*sin(angX*(3.14 / 180));
			if (map[z][x] == 0 || map[z][x] == 1 || map[z][x] == 2)
				Z -= 0.1*cos(angX*(3.14 / 180));
		}
		else
		{
			X += 0.1*sin(angX*(3.14 / 180));
			Z -= 0.1*cos(angX*(3.14 / 180));
		}
	}

	// HEAD for LEFT
	if (key == 'a')
	{
		angX -= TURN * 3;
		if (angX > 360.0) angX -= 360.0;
		if (angX < 0) angX += 360.0;
	}

	// HEAD for RIGHT
	if (key == 'd')
	{
		angX += TURN * 3;			// 곱하는 숫자가 클수록 변화가 큼
		if (angX < 0.0) angX += 360.0;
		if (angX > 360.0) angX -= 360.0;
	}

	// END the GAME
	if (key == 27 || key == 'p')
	{
		glutDestroyWindow(window);
		printf("\nE N D - G A M E \n");
		printf("E N D - G A M E \n");
		printf("E N D - G A M E \n");
		exit(0);
	}
	glutPostRedisplay();
}

void PrintTimeRemaining(void)
{
	// This static is just a hack to simplify the code. You'd normally put it in a class member.
	static int target = timeGetTime() + 1000 * 180; // 180 seconds

	int remaining = target - timeGetTime();

	printf("Time remaining: %dseconds\n", remaining / 1000);
	if ((remaining / 1000) == 1)
		if (MessageBox(NULL, L"타노스가 당신을 기다리다 지쳤습니다. \n당신은 우주에서 사라집니다.", L"타노스의 인피니티 스톤찾기", MB_OK | MB_ICONEXCLAMATION) == IDOK)
			exit(1);

	// Print the string out to the debug output window for testing

}

// BackGround Music
void sound()
{
	System_Create(&pSystem);
	pSystem->init(1, FMOD_INIT_NORMAL, NULL);

	pSystem->createSound(
		"marvel.wav",
		FMOD_LOOP_NORMAL | FMOD_HARDWARE,
		NULL,
		&pSound
	);
	FMOD_System_PlaySound((FMOD_SYSTEM*)pSystem, FMOD_CHANNEL_FREE, (FMOD_SOUND*)pSound, NULL, (FMOD_CHANNEL**)pChannel);
}

void MAKE_FLOOR(float x1, float x2, float y1, float z1, float z2, int texNum)
{
	glEnable(GL_TEXTURE_2D);
	if (texNum == 0)glBindTexture(GL_TEXTURE_2D, underFloor);		// floor image

	else glBindTexture(GL_TEXTURE_2D, startFloor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(c, c);
	glVertex3f(x2, y1, z1);
	glTexCoord2f(d, c);
	glVertex3f(x1, y1, z1);
	glTexCoord2f(d, d);
	glVertex3f(x1, y1, z2);
	glTexCoord2f(c, d);
	glVertex3f(x2, y1, z2);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}



// MAKE MAZE WALL
void MAKE_WALL(float x1, float x2, float y1, float y2, float z1, float z2, int texNum)
{

	glEnable(GL_TEXTURE_2D);

	if (texNum == 3)glBindTexture(GL_TEXTURE_2D, sideWall);
	else if (texNum == 2)glBindTexture(GL_TEXTURE_2D, endFloor);

	else if (texNum == 4)
		glBindTexture(GL_TEXTURE_2D, STONE[0]);
	else if (texNum == 5)
		glBindTexture(GL_TEXTURE_2D, STONE[1]);
	else if (texNum == 6)
		glBindTexture(GL_TEXTURE_2D, STONE[2]);
	else if (texNum == 7)
		glBindTexture(GL_TEXTURE_2D, STONE[3]);
	else if (texNum == 8)
		glBindTexture(GL_TEXTURE_2D, STONE[4]);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(a, a);
	glVertex3f(x1, y1, z1);
	glTexCoord2f(b, a);
	glVertex3f(x2, y1, z1);
	glTexCoord2f(b, b);
	glVertex3f(x2, y2, z1);
	glTexCoord2f(0.0, b);
	glVertex3f(x1, y2, z1);

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(a, a);
	glVertex3f(x1, y1, z2);
	glTexCoord2f(b, a);
	glVertex3f(x2, y1, z2);
	glTexCoord2f(b, b);
	glVertex3f(x2, y2, z2);
	glTexCoord2f(a, b);
	glVertex3f(x1, y2, z2);

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(a, a);
	glVertex3f(x1, y2, z1);
	glTexCoord2f(b, a);
	glVertex3f(x2, y2, z1);
	glTexCoord2f(b, b);
	glVertex3f(x2, y2, z2);
	glTexCoord2f(a, b);
	glVertex3f(x1, y2, z2);

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(a, a);
	glVertex3f(x1, y1, z2);
	glTexCoord2f(b, a);
	glVertex3f(x1, y1, z1);
	glTexCoord2f(b, b);
	glVertex3f(x1, y2, z1);
	glTexCoord2f(a, b);
	glVertex3f(x1, y2, z2);

	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(a, a);
	glVertex3f(x2, y1, z2);
	glTexCoord2f(b, a);
	glVertex3f(x2, y1, z1);
	glTexCoord2f(b, b);
	glVertex3f(x2, y2, z1);
	glTexCoord2f(a, b);
	glVertex3f(x2, y2, z2);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void MyDisplay()
{
	init();

	glMatrixMode(GL_MODELVIEW);

	glRotatef(angX, 0.0, 1.0, 0.0);
	glRotatef(angY, 1.0, 0.0, 0.0);
	glTranslatef(X, Y, Z);

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (map[j][i] >= 2 && map[j][i]<10)
				MAKE_WALL(0.8*i, 0.8*(i + 1), -0.4, 0.4, -0.8*j, -0.8*(j + 1), map[j][i]);
			else if (map[j][i]<2 && map[j][i] >= 0)
				MAKE_FLOOR(0.8*i, 0.8*(i + 1), -0.4, -0.8*j, -0.8*(j + 1), map[j][i]);
		}
	}



	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	if (stone_condition[0] == true)
		SV1();
	if (stone_condition[1] == true)
		SV2();
	if (stone_condition[2] == true)
		SV3();
	if (stone_condition[3] == true)
		SV4();
	if (stone_condition[4] == true)
		SV5();
	if (stone_condition[5] == true) {
		GIVE_ME();
		//Complete();
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glutSwapBuffers();


}





// function for reading image
char *READ_IMG(const char* name)
{
	FILE *f = fopen(name, "rb");
	if (f == NULL) exit(0);
	int of;
	fseek(f, 10, SEEK_SET);
	fread(&of, sizeof(int), 1, f);
	fseek(f, 4, SEEK_CUR);
	fread(&w, sizeof(int), 1, f);
	fread(&h, sizeof(int), 1, f);

	fseek(f, of, SEEK_SET);
	int j = 0;
	int by = ((w * 3 + 3) / 4) * 4 - (w * 3 % 4);
	char * tmp_m = (char *)malloc(sizeof(char) * by * h);
	char *m2 = (char *)malloc(sizeof(char) * w * h * 3);

	fread(tmp_m, sizeof(char) * by * h, 1, f);
	int x, y, i;
	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			for (i = 0; i < 3; i++)
				m2[3 * (w*y + x) + i] = tmp_m[3 * (w*y + x) + (2 - i)];
		}
	}
	free(tmp_m);
	fclose(f);
	return m2;
}

GLuint LOAD_TEXTURE(const char* c)
{
	char *wa = READ_IMG(c);
	GLuint texid;

	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, wa);
	free(wa);

	return texid;
}




int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	window = glutCreateWindow("For Thanos's Gauntlets : 타노스의 건틀렛을 위하여");
	glutFullScreen();

	glutKeyboardFunc(KeyboardHandler);
	glutMotionFunc(MouseHandler);

	init();

	if (start && !stop) {
		angX = 90;
		printf("[[   START! Let's go ! For Thanos's Gauntlets !   ]]\n\n");
		sound();
		TextureLoad();
		start = false;
	}
	else {
		pSound->release();
		pSystem->release();
		pSystem->close();
	}
	if (MessageBox(NULL, L"타노스가 당신을 기다리는 시간은 3분입니다.\n엔터키를 눌러 인피니티 스톤을 찾아 나서세요!\n\n종료를 원하시면 ESC 또는 p를 눌러주세요.", L"타노스의 인피니티 스톤찾기", MB_OK | MB_ICONEXCLAMATION) == IDOK)
	PrintTimeRemaining();			// Timer 
	glutDisplayFunc(MyDisplay);		// Display


	glutMainLoop();
	return 0;
}
