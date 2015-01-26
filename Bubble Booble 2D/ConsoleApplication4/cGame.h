#pragma once
#include "cScene.h"
#include "cPlayer.h"
#include "cData.h"
#include "cItem.h"
#include "cEnemy.h"
#include "cDisparo.h"
#include "Globals.h"


#define STATE_GAMEOVER    0
#define STATE_INTRO       1
#define STATE_RUN         2
#define STATE_PAUSE       3
#define STATE_MAINMENU    4
#define STATE_LEVELCHANGE 5
#define STATE_ENDGAME	  6

#define GAME_Xo 100
#define GAME_Yo 100
#define GAME_WIDTH 1152
#define GAME_HEIGHT 996
#define DYNAMIC_FILENAME  "items"
#define FILENAME_EXT	".txt"

#define P1_UP		'i'
#define P1_DOWN		'k'
#define P1_LEFT		'j'
#define P1_RIGHT	'l'
#define P1_SHOOT	'z'
#define P1_SKILL	'x'

#define P2_UP		GLUT_KEY_UP
#define P2_DOWN		GLUT_KEY_DOWN
#define P2_LEFT		GLUT_KEY_LEFT
#define P2_RIGHT	GLUT_KEY_RIGHT
#define P2_SHOOT	'q'
#define P2_SKILL	'w'

#define INTRO_KEY	13


class cGame

{
public:
	cGame();
	~cGame();
	bool Init();
	bool Loop();
	void Finalize();
	

	//Input
	void ReadKeyboard(unsigned char key, int x, int y,bool press);
	void ReadKeyboardUp(unsigned char key, int x, int y, bool press);
	void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	void glutPrint(float x, float y, LPVOID font, std::string text);
	void glutPrint(float x, float y, LPVOID font, std::string text, float red, float green, float blue);
	//Process
	bool Process();
	//Output
	void Render();
	void DrawIntro();
	void DrawGameOver();
	void DrawHUD();
	void DetectCollisions();
	
	void  SetState(int state);
	void  SetTime(float time);
	float  GetTime();
	

private:
	unsigned char keys[256];
	int state, level;
	float time;
	cScene Scene;
	cPlayer Player1;
	cPlayer Player2;
	cSprite Logo;
	cData Data;
	std::list<cItem*> items;
	std::list<cItem*> toads;
	std::list<cEnemy*> shells;
	std::list<cEnemy*> spines;
	std::list<cDisparo*> shoots;
	bool LoadDynamicLayer(int lvl);

};

