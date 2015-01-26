#include "cGame.h"
#include "Globals.h"


cGame::cGame()
{
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}
