#pragma once

#include "cScene.h"
#include "Globals.h"

class cDisparo 
{
public:
	cDisparo();
	~cDisparo();
	void  SetTile(int tx, int ty);
	void  SetPosition(int tx, int ty);
	int   GetX();
	int   GetY();
	int  GetState();
	int   GetWeight();
	int   GetHeight();
	void SetState(int pstate);
	void Logic(int *map);

	bool CollidesMapFloor(int *map);
	bool CollidesMapWall(int *map, bool right);


	void  Draw(int tex_id, int tex_w, int tex_h, bool run, int *map);

	void  NextFrame(int max);
	int   GetFrame();


private:

	int x, y,
		seq, delay,
		frame_delay,
		height_overground;
	int state, w, h;
	float screen_x, screen_y;
};

