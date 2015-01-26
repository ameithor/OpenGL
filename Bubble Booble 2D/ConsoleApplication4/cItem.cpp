#include "cItem.h"


cItem::cItem()
{
	seq = 0;
	delay = 0;
	frame_delay = 6;
	height_overground = TILE_SIZE / 4;
	x_trans = -1;
	y_trans = -1;
	screen_x = x;
	screen_y = y;
	state = STATE_NOT_USED;
}


cItem::~cItem()
{
}

void cItem::SetState(int state){
	this->state = state;

}

void cItem::SetTile(int tx, int ty){

	x = (tx * TILE_SIZE);
	y = (ty * TILE_SIZE);

	std::cout << x << "-" << y;

}

int cItem::GetX()
{
	return x;
}
int cItem::GetY()
{
	return y;
}

void cItem::Draw(int tex_id,int px, int py, int tex_w, int tex_h, bool run)
{
	float xo, yo, xf, yf;
	float tex_offset_x, tex_offset_y;

	tex_offset_x = 1.0f / float(tex_w / TEXTURE_TILE_SIZE);
	tex_offset_y = 1.0f / float(tex_h / TEXTURE_TILE_SIZE);

	xo = tex_offset_x * 0 + (GetFrame()*tex_offset_x);   yo = tex_offset_y + tex_offset_y * 0;
	if (run) NextFrame(4); //total de frames de la animacion

    xf = xo + tex_offset_x;
	yf = yo - tex_offset_y;



	switch (state){
		case STATE_NOT_USED:
			screen_x = x;
			screen_y = y;
		break;
		case STATE_USED://El cHeart se va de la pantalla
			screen_x = screen_x+0.1;
			std::cout << screen_y <<" -PRE\n";
			screen_y=Transition(screen_x, screen_y, 0, 0);
			//int a = Transition(1, 3, 2, -5);
			std::cout << screen_y << " -POST\n";
			
			break;
	}
	
	if (screen_y >= 1152){
		state = STATE_DELETED;
	}
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);


		glTexCoord2f(xo, yo);	glVertex2i(screen_x, screen_y);
		glTexCoord2f(xf, yo);	glVertex2i(screen_x + HEART_SIZE, screen_y);
		glTexCoord2f(xf, yf);	glVertex2i(screen_x + HEART_SIZE, screen_y + HEART_SIZE);
		glTexCoord2f(xo, yf);	glVertex2i(screen_x, screen_y + HEART_SIZE);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cItem::DrawToad(int tex_id, int px, int py, int tex_w, int tex_h, bool run)
{
	float xo, yo, xf, yf;
	float tex_offset_x, tex_offset_y;

	tex_offset_x = 1.0f / float(tex_w / TOAD_SIZE);
	tex_offset_y = 1.0f / float(tex_h / TOAD_SIZE);

	xo = tex_offset_x * 0 + (GetFrame()*tex_offset_x);   yo = tex_offset_y + tex_offset_y * 0;
	//if (run) NextFrame(4); //total de frames de la animacion

	xf = xo + tex_offset_x;
	yf = yo - tex_offset_y;

	int screen_x, screen_y;

	screen_x = x;
	screen_y = y;

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);


	glTexCoord2f(xo + 0.6666f, yo - 0.9f);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(xf + 0.6666f, yo - 0.9f);	glVertex2i(screen_x + TOAD_SIZE, screen_y);
	glTexCoord2f(xf + 0.6666f, yf - 0.9f);	glVertex2i(screen_x + TOAD_SIZE, screen_y + TOAD_SIZE);
	glTexCoord2f(xo + 0.6666f, yf - 0.9f);	glVertex2i(screen_x, screen_y + TOAD_SIZE);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

int  cItem::Transition(int x1, int y1, int x2, int y2){

	/*((x - x1) / (x2 - x1)) = ((y - y1) / (y2 - y1));
	((x - x1) * (y2 - y1)) / (x2 - x1) = (y - y1);
	y= (((x - x1) * (y2 - y1)) / (x2 - x1))+y1
	
	Ejemplo:
	A(x1,y1)-->(1,3)  
	B(x2,y2)-->(2,-5)

	y = (((x - 1) * (-5 - 3)) / (2 - 1)) + 3
	y=  [  (x-1) * -8          ] +3
	y = (-8x+8)+3
	*/

	return (((x - x1) * (y2 - y1)) / (x2 - x1)) + y1;

}
void cItem::NextFrame(int max)
{
	delay++;
	if (delay == frame_delay)
	{
		seq++;
		seq %= max;
		delay = 0;
	}
}



int cItem::GetFrame()
{
	return seq;
}



