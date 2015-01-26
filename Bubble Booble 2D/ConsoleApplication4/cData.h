#pragma once
#include "Globals.h"
#include "cTexture.h"

#define NUM_IMG		7

#define IMG_LOGO	0
#define IMG_BLOCKS	1
#define IMG_PLAYER1	2
#define IMG_PLAYER2	3
#define IMG_HEART	4
#define IMG_ITEMS	5
#define IMG_ENEMY	6

class cData
{
public:
	cData();
	~cData();

	int  GetID(int img);
	void GetSize(int img, int *w, int *h);
	bool Load();
	bool LoadImage(int img, char *filename, int type = GL_RGBA);

private:

	cTexture texture[NUM_IMG];
};

