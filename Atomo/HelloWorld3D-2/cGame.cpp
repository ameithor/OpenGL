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
	
	int t1, t2;
	GLfloat time = 30.0f;
	t1 = glutGet(GLUT_ELAPSED_TIME);
	bool res = true;
	res = Process();

	if (res) Render();
	else Finalize();

	do {
		t2 = glutGet(GLUT_ELAPSED_TIME);
		time = time - (float)(t2 - t1);
		//std::cout << time << " s\n";
	} while (t2 - t1 < 1000 / 40);   //120 fps = 1000/120
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
	
	static GLfloat fElect1 = 0.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -100.0f);

	glColor3ub(255, 0, 0);
	glutWireSphere(10.0f, 15, 15);

	glColor3ub(255, 255, 0);

	glPushMatrix();
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(90.0f, 0.0f, 0.0f);	
	glutWireSphere(6.0f, 15, 15);
	glPopMatrix();

	glColor3ub(255, 100, 0);
	glPushMatrix();
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(-70.0f, 0.0f, 0.0f);
	glutWireSphere(6.0f, 15, 15);
	glPopMatrix();


	glColor3ub(255, 0,255);
	glPushMatrix();
	glRotatef(180.0f, -45.0f, 0.0f, 0.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 60.0f);
	glutWireSphere(6.0f, 15, 15);
	glPopMatrix();

	fElect1 += 10.0f;
	if (fElect1 > 360.0f){
		fElect1 = 0.0f;

	}

	glutSwapBuffers();

}
