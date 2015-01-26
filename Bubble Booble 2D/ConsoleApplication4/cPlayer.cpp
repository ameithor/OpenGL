#include "cPlayer.h"


using namespace std;
cPlayer::cPlayer()
{
	vidas = 0;
}


cPlayer::~cPlayer()
{
}

string cPlayer::MostrarVidas(){

	string Result;          // string which will contain the result
	Result = to_string(vidas); // set 'Result' to the contents of the stream

	// 'Result' now is equal to "123" 
	return Result;

}

void cPlayer::Draw(int tex_id)
{
	float xo, yo, xf, yf;

	switch (GetState())
	{
		//1
	case STATE_LOOKLEFT:	xo = 0.0f;	yo = 0.50f;
		//NextFrame(2);
		break;
		//4
	case STATE_LOOKRIGHT:	xo = 0.25f;	yo = 0.50f;
		//NextFrame(2);
		break;
		//1..3
	case STATE_WALKLEFT:	xo = 0.0f;	yo = 0.25f + (GetFrame()*0.25f);
		NextFrame(2);
		break;
		//4..6
	case STATE_WALKRIGHT:	xo = 0.25f; yo = 0.25f + (GetFrame()*0.25f);
		NextFrame(2);
		break;

	case STATE_EAT_HEART:	xo = 0.0f + (GetFrame()*0.25f); yo = 0.0f;
		NextFrame(2);
		break;

	case STATE_COLISION:	xo = 0.25f + (GetFrame()*0.25f); yo = 0.25f;
		NextFrame(2);
		break;
	}
	xf = xo + 0.25f;
	yf = yo - 0.25f;

	DrawRect(tex_id, xo, yo, xf, yf);
	
	}
