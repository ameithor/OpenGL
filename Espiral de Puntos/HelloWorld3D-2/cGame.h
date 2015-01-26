//——— cGame.h ———//
#define GAME_Xo 100
#define GAME_Yo 100
#define GAME_WIDTH 640
#define GAME_HEIGHT 480
#define GL_PI 3.1415f

#pragma once
class cGame
{
public:
	//Main functions
	cGame();
	~cGame();
	bool Init();
	bool Loop();
	void Finalize();
	//Input
	void ReadKeyboard(unsigned char key, int x, int y,
		bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void Render();
	int xRot, yRot;
private:
	unsigned char keys[256];
};

