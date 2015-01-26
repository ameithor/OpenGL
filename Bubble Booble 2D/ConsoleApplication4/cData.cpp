#include "cData.h"


cData::cData()
{
}


cData::~cData()
{
}

int cData::GetID(int img)
{
	return texture[img].GetID();
}

void cData::GetSize(int img, int *w, int *h)
{
	texture[img].GetSize(w, h);
}

bool cData::LoadImage(int img, char *filename, int type)
{
	int res;

	res = texture[img].Load(filename, type);
	if (!res) return false;

	return true;
}


bool cData::Load()
{
	int res;

	res = LoadImage(IMG_LOGO, "Textures/logo3.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_BLOCKS, "Textures/blocks.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_PLAYER1, "Textures/bub.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_PLAYER2, "Textures/bub2.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_HEART, "Textures/heart.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_ITEMS, "Textures/items.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_ENEMY, "Textures/items.png", GL_RGBA);
	if (!res) return false;


	return true;
}