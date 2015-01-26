#pragma once
#include "cTexture.h"
#include "Globals.h"
#include "cItem.h"
#include "cData.h"


//#define SCENE_Xo		(2*TILE_SIZE)
//#define SCENE_Yo		TILE_SIZE
#define SCENE_Xo		0
#define SCENE_Yo		0
#define SCENE_WIDTH		72
#define SCENE_HEIGHT	56

#define FILENAME_LEVEL		"level"
#define FILENAME_ITEMS		"items"
#define FILENAME_EXT	".txt"

#define TILE_SIZE		16
#define TEXTURE_TILE_SIZE 16

#define BLOCK_SIZE		18
#define HEART_SIZE		32
#define ENEMY_SIZE		49
#define TOAD_SIZE		49



class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	bool LoadLevel(int level);
	bool LoadItems(int level);
	void Draw(int tex_id);
	void DrawAnimatedTiles(int tex_id, int tex_w, int tex_h);
	int *GetMap();

private:
	int map[SCENE_WIDTH * SCENE_HEIGHT];	//scene
	//std::vector<cItem*> animated_tiles;
	//std::vector<cTile> animated_tiles_up;
	//std::list<cHeart*> items;
	int id_DL;								//actual level display list
	int id_items;
};


class cRect
{
public:
	int left, top,right, bottom;
};
