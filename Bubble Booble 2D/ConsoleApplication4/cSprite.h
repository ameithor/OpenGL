#pragma once

#include "cTexture.h"
#include "Globals.h"



#define FRAME_DELAY		0
#define STEP_LENGTH		4
#define JUMP_HEIGHT		96
#define DAMAGE_HEIGHT	24
#define JUMP_STEP		2
#define DAMAGE_STEP		3

#define STATE_LOOKLEFT		0
#define STATE_LOOKRIGHT		1
#define STATE_WALKLEFT		2
#define STATE_WALKRIGHT		3
#define STATE_EAT_HEART		4
#define STATE_COLISION		5

typedef struct {
	int left, top,
		right, bottom;
} Rect;

class cSprite
{
public:
	cSprite();
	~cSprite();

	void SetPosition(int x, int y);
	void GetPosition(int *x, int *y);
	void SetTile(int tx, int ty);
	void GetTile(int *tx, int *ty);
	void SetWidthHeight(int w, int h);
	void GetWidthHeight(int *w, int *h);
	bool  CollisionCircle(int rx, int ry, int rh, int rw);
	int   Distance(int x1, int y1, int x2, int y2);

	int   GetX();
	int   GetY();
	int   GetHeight();
	int   GetWeight();

	bool Collides(Rect *rc);

	bool CollidesMapWall(int *map, bool right);
	bool CollidesMapFloor(int *map);
	void GetArea(Rect *rc);
	
	
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf);


	bool Collision(cSprite *sprite);
	bool Collision(int x, int y , int h, int w);
	

	void MoveRight(int *map);
	void MoveLeft(int *map);
	void Jump(int *map);
	void Damage(int *map);
	void Stop();
	void Logic(int *map);

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();

private:
	int x, y;
	int w, h;
	int radius_x, radius_y;
	int state;
	int hit_h, hit_w;

	bool jumping;
	bool damaging;
	int jump_alfa;
	int jump_y;
	int jump_x;

	int seq, delay;

};

