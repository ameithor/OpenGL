#include "cGame.h"
#include "Globals.h"


cGame::cGame()
{
	xRot = 100.0f;
	yRot = 200.0f;
}


cGame::~cGame()
{
}



//Game initializations
bool cGame::Init()
{
	return true;
}
//Game loop
bool cGame::Loop()
{
	bool res = true;
	res = Process();

	if (res) Render();
	else Finalize();

	return res;
}
//Game finalizations
void cGame::Finalize()
{
}

//Game input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}
void cGame::ReadMouse(int button, int state, int x, int y)
{
}
//Game process
bool cGame::Process()
{
	bool end = true;

	//Process Input
	if (keys[27]){
		end = false;
	} //27=ESC
	//Game Logic
	//...
	return end;
}
//Game output
void cGame::Render()
{
	GLfloat x, y, z, angle;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f,0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);

	//Save matrix state and do the rotation
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glBegin(GL_POINTS);
	
	z = -50.0f;
	for (angle = 0.0f; angle <= (2.0f*GL_PI) * 3.0f; angle += 0.1f){
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);

		glVertex3f(x, y, z);

		z += 0.5f;

	}

	glEnd();
	glPopMatrix();


	glutSwapBuffers();
}
