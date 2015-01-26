#include "cSprite.h"
#include "cScene.h"
#include "cGame.h"


cSprite::cSprite()
{
	seq = 0;
	w = TILE_SIZE;
	h = TILE_SIZE;
	delay = 6;
	radius_x = TILE_SIZE / 2;
	radius_y = TILE_SIZE / 2;

}


cSprite::~cSprite()
{
}


void cSprite::SetPosition(int posx, int posy)
{
	x = posx;
	y = posy;
}
void cSprite::GetPosition(int *posx, int *posy)
{
	*posx = x;
	*posy = y;
}


void cSprite::SetTile(int tx, int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}
void cSprite::GetTile(int *tx, int *ty)
{
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void cSprite::SetWidthHeight(int width, int height)
{
	w = width;
	h = height;
}
void cSprite::GetWidthHeight(int *width, int *height)
{
	*width = w;
	*height = h;
}

bool cSprite::Collides(Rect *rc)
{
	return ((x>rc->left) && (x + w<rc->right) && (y>rc->bottom) && (y + h<rc->top));
}





bool cSprite::CollidesMapWall(int *map, bool right)
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

bool cSprite::CollidesMapFloor(int *map)
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

void cSprite::GetArea(Rect *rc)
{
	rc->left = x;
	rc->right = x + w;
	rc->bottom = y;
	rc->top = y + h;
}




void cSprite::DrawRect(int tex_id, float xo, float yo, float xf, float yf)
{
	int screen_x, screen_y;

	screen_x = x + SCENE_Xo;
	screen_y = y + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(xo, yo);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(xf, yo);	glVertex2i(screen_x + w, screen_y);
	glTexCoord2f(xf, yf);	glVertex2i(screen_x + w, screen_y + h);
	glTexCoord2f(xo, yf);	glVertex2i(screen_x, screen_y + h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cSprite::MoveLeft(int *map)
{
	int xaux;

	//Whats next tile?
	if ((x % TILE_SIZE) == 0)
	{
		xaux = x;
		x -= STEP_LENGTH;

		if (CollidesMapWall(map, false))
		{
			x = xaux;
			state = STATE_LOOKLEFT;
		}
	}
	//Advance, no problem
	else
	{
		x -= STEP_LENGTH;
		if (state != STATE_WALKLEFT)
		{
			state = STATE_WALKLEFT;
			seq = 0;
			delay = 0;
		}
	}
	if (x == 0){
		x = GAME_WIDTH-w;
	}
}

void cSprite::MoveRight(int *map)
{
	int xaux;

	//Whats next tile?
	if ((x % TILE_SIZE) == 0)
	{
		xaux = x;
		x += STEP_LENGTH;

		if (CollidesMapWall(map, true))
		{
			x = xaux;
			state = STATE_LOOKRIGHT;
			
		}
	}
	//Advance, no problem
	else
	{
		x += STEP_LENGTH;

		if (state != STATE_WALKRIGHT)
		{
			state = STATE_WALKRIGHT;
			seq = 0;
			delay = 0;
		}
	}

	if (x+w == GAME_WIDTH){
		x = 0;
	}
}

void cSprite::Jump(int *map)
{
	if (!jumping)
	
	{
		if (CollidesMapFloor(map))
		{
			jumping = true;
			jump_alfa = 0;
			jump_y = y;
		}
	}
}

void cSprite::Damage(int *map)
{
	
		if (CollidesMapFloor(map))
		{
			
			damaging=true;
			jump_alfa = 0;
			jump_y = y;
		}
	
}

void cSprite::Stop()
{
	switch (state)
	{
	case STATE_WALKLEFT:	state = STATE_LOOKLEFT;		break;
	case STATE_WALKRIGHT:	state = STATE_LOOKRIGHT;	break;
	}
}

void cSprite::Logic(int *map)
{
	float alfa;

	if (jumping)
	{
		jump_alfa += JUMP_STEP;

		if (jump_alfa == 180)
		{
			jumping = false;
			y = jump_y;
		}
		else
		{
			alfa = ((float)jump_alfa) * 0.017453f;
			y = jump_y + (int)(((float)JUMP_HEIGHT) * sin(alfa));

			if (jump_alfa > 90)
			{
				//Over floor?
				jumping = !CollidesMapFloor(map);
			}
		}
	}
	else if (damaging){
		jump_alfa += DAMAGE_STEP;

		if (jump_alfa == 180)
		{
			damaging = false;
			y = jump_y;
		}
		else
		{
			alfa = ((float)jump_alfa) * 0.017453f;
			y = jump_y + (int)(((float)DAMAGE_HEIGHT) * sin(alfa));
			
			if (jump_alfa > 90)
			{
				//Over floor?
				damaging = !CollidesMapFloor(map);
			}
		}
	}
	else
	{
		//Over floor?
		if (!CollidesMapFloor(map))
			y -= (2 * STEP_LENGTH);
	}
}

bool cSprite::Collision(cSprite *sprite){

	
	return  (x < sprite->GetX() + sprite->w) && // [x,x+a], [X,X+A] intersection
		(sprite->GetX() < x + w) && // [x,x+a], [X,X+A] intersection
		(y < sprite->GetY() + sprite->h) && // [y,y+b], [Y,Y+B] intersection
		(sprite->GetY() < y + h);              // [y,y+b], [Y,Y+B] intersection

	
}

bool cSprite::Collision(int rx, int ry, int rh, int rw){


	return  (x < rx + rw) && // [x,x+a], [X,X+A] intersection
		(rx < x + w) && // [x,x+a], [X,X+A] intersection
		(y < ry + rh) && // [y,y+b], [Y,Y+B] intersection
		(ry < y + h);              // [y,y+b], [Y,Y+B] intersection


}


int cSprite::GetX()
{
	return x;
}
int cSprite::GetY()
{
	return y;
}

int cSprite::GetHeight()
{
	return h;
}
int cSprite::GetWeight()
{
	return w;
}

int cSprite::Distance(int x1, int y1, int x2, int y2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

bool cSprite::CollisionCircle(int rx, int ry, int rh, int rw){

	int center_x1 = x + (w >> 1);
	int center_y1 = y + (h >> 1);
	int center_x2 = rx + (rw >> 1);
	int center_y2 = ry + (rh >> 1);

	int radius2 = (rw / 2);

	int delta = Distance(center_x1, center_y1, center_x2, center_y2);
	int sum_radius = radius_x + radius2;

	if (delta <= sum_radius) return true;
	else return false;
}



void cSprite::NextFrame(int max)
{
	delay++;
	if (delay == FRAME_DELAY)
	{
		seq++;
		seq %= max;
		delay =10;
	}
}
int cSprite::GetFrame()
{
	return seq;
}
int cSprite::GetState()
{
	return state;
}
void cSprite::SetState(int s)
{
	state = s;
}

