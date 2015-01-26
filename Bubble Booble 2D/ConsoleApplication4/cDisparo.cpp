#include "cDisparo.h"
#include "cScene.h"

#define STATE_LOOKLEFT		0
#define STATE_LOOKRIGHT		1
#define STATE_WALKLEFT		2
#define STATE_WALKRIGHT		3

cDisparo::cDisparo()
{
	seq = 0;
	delay = 0;
	frame_delay = 6;
	screen_x = 1.0f;
	state = STATE_LOOKLEFT;
	w = ENEMY_SIZE;
	h = ENEMY_SIZE;
	height_overground = TILE_SIZE / 4;
}


cDisparo::~cDisparo()
{
}

void cDisparo::SetTile(int tx, int ty){

	this->x = (tx * TILE_SIZE);
	this->y = (ty * TILE_SIZE);
	screen_x = this->x;


}




int cDisparo::GetX()
{
	return x;
}
int cDisparo::GetY()
{
	return y;
}

void cDisparo::SetPosition(int tx, int ty){
	this->x = tx;
	this->y = ty;
	screen_x = tx;
}

bool cDisparo::CollidesMapWall(int *map, bool right)
{
	int tile_x, tile_y;
	int j;
	int width_tiles, height_tiles;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;
	width_tiles = w / TILE_SIZE;
	height_tiles = h / TILE_SIZE;

	if (right)	tile_x += width_tiles;

	for (j = 0; j<height_tiles; j++)
	{
		if (map[tile_x + ((tile_y + j)*SCENE_WIDTH)] != 0)	return true;
	}

	return false;
}

void cDisparo::Draw(int tex_id, int tex_w, int tex_h, bool run, int *map)
{
	float xo, yo, xf, yf;
	float tex_offset_x, tex_offset_y;



	tex_offset_x = 1.0f / float(tex_w / ENEMY_SIZE);
	tex_offset_y = 1.0f / float(tex_h / ENEMY_SIZE);


	xo = tex_offset_x * 0 + (GetFrame()*tex_offset_x);   yo = tex_offset_y + tex_offset_y * 0;
	//if (run) NextFrame(4); //total de frames de la animacion

	xf = xo + tex_offset_x;
	yf = yo - tex_offset_y;

	switch (GetState())
	{
	case STATE_LOOKLEFT:
		screen_x = screen_x - 0.6f;
		//NextFrame(4);
		break;
	case STATE_WALKLEFT:
		screen_x = screen_x - 0.6f;
		//NextFrame(4);
		break;

	case STATE_LOOKRIGHT:
		screen_x = screen_x + 0.6f;
		//NextFrame(4);
		break;
	case STATE_WALKRIGHT:
		screen_x = screen_x - 0.6f;
		//NextFrame(4);
		break;
	}

	x = screen_x;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);

	glTexCoord2f(xo + 0.32f, yo - 0.32f);	glVertex2i(x, y);
	glTexCoord2f(xf + 0.32f, yo - 0.32f);	glVertex2i(x + ENEMY_SIZE, y);
	glTexCoord2f(xf + 0.32f, yf - 0.32f);	glVertex2i(x + ENEMY_SIZE, y + ENEMY_SIZE);
	glTexCoord2f(xo + 0.32f, yf - 0.32f);	glVertex2i(x, y + ENEMY_SIZE);


	glEnd();
	glDisable(GL_TEXTURE_2D);
}




int cDisparo::GetState(){

	return this->state;
}
void cDisparo::SetState(int pstate){

	this->state = pstate;
}
void cDisparo::NextFrame(int max)
{
	delay++;
	if (delay == frame_delay)
	{
		seq++;
		seq %= max;
		delay = 5.999;
	}
}

int cDisparo::GetHeight()
{
	return h;
}
int cDisparo::GetWeight()
{
	return w;
}

void cDisparo::Logic(int *map){

	if (!CollidesMapFloor(map))
		y -= (2 * STEP_LENGTH);

	/*if (CollidesMapWall(map, false) && (state == SHOTLEFT)){

		state = SHOTRIGHT;

	}
	else if (CollidesMapWall(map, true) && (state == SHOTRIGHT)){

		state = SHOTLEFT;
	}
	*/


}
bool cDisparo::CollidesMapFloor(int *map)
{
	int tile_x, tile_y;
	int width_tiles;
	bool on_base;
	int i;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;

	width_tiles = w / TILE_SIZE;
	if ((x % TILE_SIZE) != 0) width_tiles++;

	on_base = false;
	i = 0;
	while ((i<width_tiles) && !on_base)
	{
		if ((y % TILE_SIZE) == 0)
		{
			if (map[(tile_x + i) + ((tile_y - 1) * SCENE_WIDTH)] != 0)
				on_base = true;
		}
		else
		{
			if (map[(tile_x + i) + (tile_y * SCENE_WIDTH)] != 0)
			{
				y = (tile_y + 1) * TILE_SIZE;
				on_base = true;
			}
		}
		i++;
	}
	return on_base;
}

int cDisparo::GetFrame()
{
	return seq;
}


