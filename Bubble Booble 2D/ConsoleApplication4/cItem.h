#pragma once

#include "cScene.h"
#include "cPlayer.h"

#define STATE_NOT_USED 0
#define STATE_USED 1
#define STATE_DELETED 2

class cItem : public cSprite
{
public:
	cItem();
	~cItem();

	void  SetTile(int tx, int ty);
	int   GetX();
	int   GetY();
	
	void  Draw(int tex_id,int px, int py, int tex_w, int tex_h, bool run);
	int  Transition( int x1, int y1, int x2, int y2);
	void  DrawToad(int tex_id, int px, int py, int tex_w, int tex_h, bool run);

	void  NextFrame(int max);
	int   GetFrame();
	int screen_x, screen_y;
	void SetState(int State);

private:

	int x, y,
		seq, delay,
		frame_delay,
		state, height_overground, x_trans, y_trans;
	
};

class cHeart : public cItem
{
public:
	bool Effect(cPlayer &player)
	{
	/*	if (player.GetHealth() == player.GetMaxHealth()) return false;
		int new_health = player.GetHealth() + 40;
		if (new_health > player.GetMaxHealth()) player.SetHealth(player.GetMaxHealth());
		else player.SetHealth(new_health);
		return true;
		*/
		return true;
	}
};

class cToad : public cItem
{
public:
	bool Effect(cPlayer &player)
	{
		/*	if (player.GetHealth() == player.GetMaxHealth()) return false;
		int new_health = player.GetHealth() + 40;
		if (new_health > player.GetMaxHealth()) player.SetHealth(player.GetMaxHealth());
		else player.SetHealth(new_health);
		return true;
		*/
		return true;
	}
};