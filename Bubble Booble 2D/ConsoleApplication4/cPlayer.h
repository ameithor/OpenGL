#pragma once

#include "cSprite.h"


#define PLAYER_START_CX		3
#define PLAYER_START_CY		2 



class cPlayer : public cSprite
{
public:
	cPlayer();
	~cPlayer();
	
	std::string MostrarVidas();
	int vidas;
	void Draw(int tex_id);

	
};

