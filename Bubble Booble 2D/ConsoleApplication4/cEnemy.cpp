#include "cEnemy.h"
#include "cScene.h"


cEnemy::cEnemy()
{
	seq = 0;
	delay = 0;
	frame_delay = 6;
	screen_x = 1.0f;
	state = WALKLEFT;
	w = ENEMY_SIZE;
	h = ENEMY_SIZE;
	radius = (w / 2);
	height_overground = TILE_SIZE / 4;
}


cEnemy::~cEnemy()
{
}

void cEnemy::SetTile(int tx, int ty){

	this->x = (tx * TILE_SIZE);
	this->y = (ty * TILE_SIZE);
	screen_x = this->x;


}

int cEnemy::GetX()
{
	return x;
}
int cEnemy::GetY()
{
	return y;
}

void cEnemy::SetPosition(int tx, int ty){
	this->x = tx;
	this->y = ty;

}

bool cEnemy::Collision(int rx, int ry, int rh, int rw){


	return  (x < rx + rw) && // [x,x+a], [X,X+A] intersection
		(rx < x + w) && // [x,x+a], [X,X+A] intersection
		(y < ry + rh) && // [y,y+b], [Y,Y+B] intersection
		(ry < y + h);              // [y,y+b], [Y,Y+B] intersection


}

int cEnemy::Distance(int x1, int y1, int x2, int y2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

bool cEnemy::CollisionCircle(int rx, int ry, int rh, int rw){

	int center_x1 = x + (w >> 1);
	int center_y1 = y + (h >> 1);
	int center_x2 = rx + (rw >> 1);
	int center_y2 = ry + (rh>> 1);

	int radius2 = (rw / 2);

	int delta = Distance(center_x1, center_y1, center_x2, center_y2);
	int sum_radius = radius + radius2;

	if (delta <= sum_radius) return true;
	else return false;
}

	



bool cEnemy::CollidesMapWall(int *map, bool right)
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

void cEnemy::Draw(int tex_id,  int tex_w, int tex_h, bool run, int *map)
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
	case WALKLEFT:	
		screen_x = screen_x - 0.2f;
		//NextFrame(4);
		break;

	case WALKRIGHT:	
		screen_x = screen_x + 0.2f;
		//NextFrame(4);
		break;
	}
	
	x = screen_x;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	
	glTexCoord2f(xo + 0.6666f, yo-0.32f);	glVertex2i(x, y);
	glTexCoord2f(xf + 0.6666f, yo - 0.32f);	glVertex2i(x + ENEMY_SIZE, y);
	glTexCoord2f(xf + 0.6666f, yf - 0.32f);	glVertex2i(x + ENEMY_SIZE, y + ENEMY_SIZE);
	glTexCoord2f(xo + 0.66f, yf - 0.32f);	glVertex2i(x, y + ENEMY_SIZE);


	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void cEnemy::DrawSpine(int tex_id, int tex_w, int tex_h, bool run, int *map)
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
	case WALKLEFT:
		screen_x = screen_x - 0.2f;
		//NextFrame(4);
		break;

	case WALKRIGHT:
		screen_x = screen_x + 0.2f;
		//NextFrame(4);
		break;
	}

	x = screen_x;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);

	glTexCoord2f(xo + 0.32f, yo - 0.20f);	glVertex2i(x, y);
	glTexCoord2f(xf + 0.32f, yo - 0.20f);	glVertex2i(x + ENEMY_SIZE, y);
	glTexCoord2f(xf + 0.32f, yf - 0.20f);	glVertex2i(x + ENEMY_SIZE, y + ENEMY_SIZE);
	glTexCoord2f(xo + 0.32f, yf - 0.20f);	glVertex2i(x, y + ENEMY_SIZE);


	glEnd();
	glDisable(GL_TEXTURE_2D);
}


int cEnemy::GetState(){

	return this->state;
}
void cEnemy::SetState(int pstate){

	this->state = pstate;
}
void cEnemy::NextFrame(int max)
{
	delay++;
	if (delay == frame_delay)
	{
		seq++;
		seq %= max;
		delay =5.999;
	}
}

int cEnemy::GetHeight()
{
	return h;
}
int cEnemy::GetWeight()
{
	return w;
}

void cEnemy::Logic(int *map){

	if (!CollidesMapFloor(map) && (state == WALKLEFT)){
		state = WALKRIGHT;		//el enemy vuelve hacia dentro de su carril

	}
	else if (!CollidesMapFloor(map) && (state == WALKRIGHT)){
		state = WALKLEFT;		//y -= (2 * STEP_LENGTH); --> Si nos interesase que caiga hacia abajo
	}

	if (CollidesMapWall(map, false) && (state==WALKLEFT)){
	
		state = WALKRIGHT;

	}
	else if (CollidesMapWall(map, true) && (state == WALKRIGHT)){
	
		state = WALKLEFT;
	}
	

}
bool cEnemy::CollidesMapFloor(int *map)
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

int cEnemy::GetFrame()
{
	return seq;
}

