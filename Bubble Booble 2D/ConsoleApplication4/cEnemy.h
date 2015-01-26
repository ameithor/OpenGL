#pragma once

#include "cScene.h"

#define WALKLEFT		0
#define WALKRIGHT		1

class cEnemy
{
public:
	cEnemy();
	~cEnemy();

	void  SetTile(int tx, int ty);
	void  SetPosition(int tx, int ty);
	int   GetX();
	int   GetY();
	int   GetState();
	int   GetWeight();
	int   GetHeight();
	void  SetState(int pstate);
	void  Logic(int *map);

	bool  CollidesMapFloor(int *map);
	bool  CollidesMapWall(int *map, bool right);
	bool  Collision(int rx, int ry, int rh, int rw);
	bool  CollisionCircle(int rx, int ry, int rh, int rw);
	int   Distance(int x1, int y1, int x2, int y2);

	void  Draw(int tex_id, int tex_w, int tex_h, bool run, int *map);
	void  DrawSpine(int tex_id, int tex_w, int tex_h, bool run, int *map);

	void  NextFrame(int max);
	int   GetFrame();


private:

	int x, y,
		seq, delay,
		frame_delay,
		height_overground;
	int state,w,h,radius;
	float screen_x, screen_y;

};

class cEnemy2 : public cEnemy
{
public:

};

