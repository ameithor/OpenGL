#include "Globals.h"
#include "cGame.h"




cGame::cGame()
{

	time = 1.0f;
}


cGame::~cGame()
{
}

/*void TimerFunction(int n)
{
	n--;
	//std::cout <<n<< "n \n";

	if (n > 0){
		glutTimerFunc(1000, TimerFunction, n);
	}
	

}*/

void cGame::DrawGameOver(){
	std::cout << "FINAL!!!!!";

}
 void cGame::SetState(int state){
	this->state = state;
}

 void cGame::SetTime(float time){
	 this->time = time;
 }

 float cGame::GetTime(){
	 return this->time;
 }

//Game initializations
bool cGame::Init()
{
	time = 30.0f;
	

	bool res = true;
	state = STATE_INTRO;
	
	//Graphics initialization
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);

	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	res = Data.Load();
	if (!res) return false;
	LoadDynamicLayer(3);
	res = Scene.LoadLevel(3);
	if (!res) return false;

	
	return res;
	
}


bool cGame::LoadDynamicLayer(int lvl)
{
	bool res;
	FILE *fd;
	char file[32];
	int i, j;
	
	char tile;

	res = true;

	if (level<10) sprintf(file, "Levels/%s0%d%s", (char *)DYNAMIC_FILENAME, lvl, (char *)FILENAME_EXT);
	else		 sprintf(file, "Levels/%s%d%s", (char *)DYNAMIC_FILENAME, lvl, (char *)FILENAME_EXT);

	fd = fopen(file, "r");
	if (fd == NULL) return false;

	for (j = SCENE_HEIGHT-1; j >= 0; j--)
	{
		for (i = 0; i<SCENE_WIDTH; i++)
		{
			
			fscanf(fd, "%c", &tile);
			
			//std::cout << " tile " <<  i << "-" <<  j << "-->" << tile<<"\n";
			if (tile == '5')
			{
				//std::cout << "New heart en el tile " << 72-i << "-" << 56-j << "\n";
				items.push_back(new cHeart);
				items.back()->SetTile(i, j);

			}
			if (tile == '7')
			{
				//std::cout << "New heart en el tile " << 72-i << "-" << 56-j << "\n";
				toads.push_back(new cToad);
				toads.back()->SetTile(i, j);

			}
			if (tile == '8')
			{
				//std::cout << "New heart en el tile " << 72-i << "-" << 56-j << "\n";
				spines.push_back(new cEnemy2);
				spines.back()->SetTile(i, j);

			}
			if (tile == '6')
			{
				//std::cout << "New heart en el tile " << 72-i << "-" << 56-j << "\n";
				shells.push_back(new cEnemy);
				shells.back()->SetTile(i, j);

			}
			if (tile == '9')
			{
				Player2.SetTile(i, j);
				Player2.SetWidthHeight(64, 64);
				Player2.SetState(STATE_LOOKLEFT);

			}
			if (tile == '0')
			{
				
				Player1.SetTile(i, j);
				Player1.SetWidthHeight(64, 64);
				Player1.SetState(STATE_LOOKLEFT);

			}
			 //pass comma or enter
		}
		fscanf(fd, "%c", &tile);
		std::cout << "\n";
	}

	fclose(fd);
	return res;
}


//Game loop
bool cGame::Loop()
{
	bool res = true;
	int t1, t2;
	time = 30.0f;
	t1 = glutGet(GLUT_ELAPSED_TIME);
	


		res = Process();
		if (res) Render();
	


	do {
		t2 = glutGet(GLUT_ELAPSED_TIME);
		time = time - (float)(t2 - t1);
		//std::cout << time << " s\n";
	} while (t2 - t1 < 1000 / 120);   //120 fps = 1000/120

	return res;
		
}

//Game finalizations
void cGame::Finalize()
{
}


//Game input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;

	if (key == 27) { // If Escape has been pressed Application will be colsed
		
		exit(0);
		
	}
	

	if (key != GLUT_KEY_UP && key != GLUT_KEY_DOWN && key != GLUT_KEY_LEFT && key != GLUT_KEY_RIGHT) keys[key] = press;
}

void cGame::ReadKeyboardUp(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;

	if (key == 27) { // If Escape has been pressed Application will be colsed

		exit(0);

	}


	if (key != GLUT_KEY_UP && key != GLUT_KEY_DOWN && key != GLUT_KEY_LEFT && key != GLUT_KEY_RIGHT) keys[key] = press;
}
void cGame::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
{
	//cuando se deja de pulsar una tecla de direccion lateral cuando se desplaza en diagonal, los frames de los player pueden cambiar


	if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN || key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT || key == INTRO_KEY) keys[key] = press;

}

void cGame::ReadMouse(int button, int state, int x, int y)
{
}

void cGame::DetectCollisions(){
	if (!items.empty()){

		std::list<cItem*>::iterator it_t;
		it_t = items.begin();

		for (it_t = items.begin(); it_t != items.end();)
		{
			bool used = false;
			bool deleted = false;
			int rx = (*it_t)->GetX();
			int ry = (*it_t)->GetY();
			int rh = (*it_t)->GetHeight();
			int rw = (*it_t)->GetWeight();

			if (Player1.Collision(rx, ry, rh, rw)&& ((*it_t)->GetState()!=STATE_USED)){

				if (static_cast<cHeart*>(*it_t) != NULL){ //verificamos a que subclase pertenece el puntero
					Player1.SetState(STATE_EAT_HEART);
					Player1.vidas++;
					(*it_t)->screen_y = ry;
					(*it_t)->screen_x = rx;
					//(*it_t)->SetState(STATE_USED);
					used = true;
				}
			}
			if (Player2.Collision(rx, ry, rh, rw) && ((*it_t)->GetState() != STATE_USED)){

				if (static_cast<cHeart*>(*it_t) != NULL){ //verificamos a que subclase pertenece el puntero
					Player2.SetState(STATE_EAT_HEART);
					Player2.vidas++;
					(*it_t)->screen_y = ry;
					(*it_t)->screen_x = rx;
					//(*it_t)->SetState(STATE_USED);
					used = true;
				}
			}
			
			if (used)
			{
				//std::cout << " borrado";
				delete (*it_t);
				it_t = items.erase(it_t);
				//Sound.Play(SOUND_TOKEN);
				it_t++;
			}
			else {

				it_t++;
			}
			
		}

	}
	else{
		SetState(STATE_GAMEOVER);
	}

	if (!shoots.empty()){

		std::list<cDisparo*>::iterator it_ts;
		it_ts = shoots.begin();

		for (it_ts = shoots.begin(); it_ts != shoots.end();)
		{
			bool used = false;
			int rx = (*it_ts)->GetX();
			int ry = (*it_ts)->GetY();
			int rh = (*it_ts)->GetHeight();
			int rw = (*it_ts)->GetWeight();

			if (Player1.Collision(rx, ry, rh, rw)){

				if (static_cast<cDisparo*>(*it_ts) != NULL){ //verificamos a que subclase pertenece el puntero
					Player1.vidas--;
					Player1.Damage(Scene.GetMap());
					used = true;
				}
			}
			if (Player2.Collision(rx, ry, rh, rw)){

				if (static_cast<cDisparo*>(*it_ts) != NULL){ //verificamos a que subclase pertenece el puntero
					Player2.vidas--;
					Player2.Damage(Scene.GetMap());
					used = true;
				}
			}

			if (used)
			{
			
				delete (*it_ts);
				it_ts = shoots.erase(it_ts);
				//Sound.Play(SOUND_TOKEN);
			}
			else{
				it_ts++;
			}
		}
	}

		/*	std::list<cEnemy*>::iterator it_tsp;
			it_tsp = spines.begin();

			for (it_tsp = spines.begin(); it_tsp != spines.end();)
			{


				if ((dynamic_cast<cEnemy*>(*it_tsp) != NULL) && ((*it_tsp)->Collision(rx, ry, rh, rw))){ //verificamos a que subclase pertenece el puntero
						
					Player2.vidas = 950;
					}
			

			}

		}

	}
	*/

	if (!toads.empty()){

		std::list<cItem*>::iterator it_to;
		it_to = toads.begin();

		for (it_to = toads.begin(); it_to != toads.end();)
		{
			bool used = false;
			int rx = (*it_to)->GetX();
			int ry = (*it_to)->GetY();
			int rh = (*it_to)->GetHeight();
			int rw = (*it_to)->GetWeight();

			if (Player1.Collision(rx, ry, rh, rw)){

				if (static_cast<cToad*>(*it_to) != NULL){ //verificamos a que subclase pertenece el puntero
					Player1.vidas++;
					int w = Player1.GetWeight();
					int h = Player1.GetHeight();
					w = w + 20;
					h = h + 20;
					Player1.SetWidthHeight(w, h);
					used = true;
				}
			}
			if (Player2.CollisionCircle(rx, ry, rh, rw)){

				if (static_cast<cToad*>(*it_to) != NULL){ //verificamos a que subclase pertenece el puntero
					Player2.vidas++;
					int w = Player2.GetWeight();
					int h = Player2.GetHeight();
					w = w + 20;
					h = h + 20;
					Player2.SetWidthHeight(w, h);
					used = true;
				}
			}
			if (used)
			{
				std::cout << " borrado";
				delete (*it_to);
				it_to = toads.erase(it_to);
				//Sound.Play(SOUND_TOKEN);
			}
			else{
				it_to++;
			}
		}

	}
	


	if (!shells.empty()){

		std::list<cEnemy*>::iterator it_e;
		it_e = shells.begin();

		for (it_e = shells.begin(); it_e != shells.end();)
		{
			(*it_e)->Logic(Scene.GetMap());
			bool used = false;
			int rx = (*it_e)->GetX();
			int ry = (*it_e)->GetY();
			int rh = (*it_e)->GetHeight();
			int rw = (*it_e)->GetWeight();


			if (Player1.CollisionCircle(rx, ry, rh, rw)){
				std::cout << " enemigo colision\n";
				if (dynamic_cast<cEnemy*>(*it_e) != NULL){ //verificamos a que subclase pertenece el puntero  
					Player1.vidas--;
					Player1.Damage(Scene.GetMap());
					used = true;
				}
			}
			if (Player2.CollisionCircle(rx, ry, rh, rw)){
				std::cout << " enemigo colision\n";
				if (dynamic_cast<cEnemy*>(*it_e) != NULL){ //verificamos a que subclase pertenece el puntero
					Player2.vidas--;
					Player2.Damage(Scene.GetMap());
					used = true;
				}
			}
			if (used)
			{
				//std::cout << " shell  borrado";
				//delete (*it_e);
				//it_e = shells.erase(it_e);
				//Sound.Play(SOUND_TOKEN);
				it_e++;
			}
			else{
				it_e++;
			}
		}

	}

	if (!spines.empty()){

		std::list<cEnemy*>::iterator it_ts;
		it_ts = spines.begin();

		for (it_ts = spines.begin(); it_ts != spines.end();)
		{
			(*it_ts)->Logic(Scene.GetMap());
			bool used = false;
			int rx = (*it_ts)->GetX();
			int ry = (*it_ts)->GetY();
			int rh = (*it_ts)->GetHeight();
			int rw = (*it_ts)->GetWeight();


			if (Player1.CollisionCircle(rx, ry, rh, rw)){
				if (dynamic_cast<cEnemy*>(*it_ts) != NULL){ //verificamos a que subclase pertenece el puntero  
					Player2.vidas=99;
					//Player1.Damage(Scene.GetMap());
					SetState(STATE_GAMEOVER);
					used = true;
				}
			}
			if (Player2.CollisionCircle(rx, ry, rh, rw)){
				if (dynamic_cast<cEnemy*>(*it_ts) != NULL){ //verificamos a que subclase pertenece el puntero
					Player1.vidas=99;
					//Player2.Damage(Scene.GetMap());
					SetState(STATE_GAMEOVER);
					used = true;
				}
			}
			if (used)
			{
				std::cout << " enemigo borrado";
				delete (*it_ts);
				it_ts = spines.erase(it_ts);
				//Sound.Play(SOUND_TOKEN);
			}
			else{
				it_ts++;
			}
		}

	}
}


//Game process
bool cGame::Process()
{
	bool res = true;
	bool P2_SHOOT_UP = NULL;
	int tex_w, tex_h;
	//Process Input
	if (keys[27])	res = false;
	if (keys[INTRO_KEY] && state == STATE_INTRO)	state = STATE_RUN;

	if (state == STATE_RUN) {
		if (keys[P1_UP]){
			Player1.Jump(Scene.GetMap());
			keys[P1_UP] = false;
		}
		if (keys[P1_LEFT]){
			Player1.MoveLeft(Scene.GetMap());
			
		}
		else if (keys[P1_RIGHT]){
			Player1.MoveRight(Scene.GetMap());
			
		}else if (keys[P1_SHOOT])
		{
				
				Data.GetSize(IMG_ITEMS, &tex_w, &tex_h);
				shoots.push_back(new cDisparo);
				if (Player1.GetState() == (STATE_LOOKLEFT)){

					shoots.back()->SetPosition(Player1.GetX()-90.0f, Player1.GetY());

				}
				
				if (Player1.GetState() == (STATE_LOOKRIGHT)){
					shoots.back()->SetPosition(Player1.GetX() + 90.0f, Player1.GetY());
				}
				
				shoots.back()->SetState(Player1.GetState());
				keys[P1_SHOOT] = false;
			
		}
		else{
			Player1.Stop();
		}

		if (keys[P2_UP]){
			Player2.Jump(Scene.GetMap());
			keys[P2_UP] = false;
		}
		if (keys[P2_LEFT]){
			Player2.MoveLeft(Scene.GetMap());
			
		}
		else if (keys[P2_RIGHT]){
			Player2.MoveRight(Scene.GetMap());
			
		}
		else if (keys[P2_SHOOT])
		{
			
			std::cout << "pulsado\n";
			Data.GetSize(IMG_ITEMS, &tex_w, &tex_h);
			shoots.push_back(new cDisparo);
			if (Player2.GetState() == (STATE_LOOKLEFT)){

				shoots.back()->SetPosition(Player2.GetX() - 90.0f, Player2.GetY());

			}

			if (Player2.GetState() == (STATE_LOOKRIGHT)){
				shoots.back()->SetPosition(Player2.GetX() + 90.0f, Player2.GetY());
			}
			shoots.back()->SetState(Player2.GetState());
			keys[P2_SHOOT] = false;
		}
		else{
			Player2.Stop();
		}


		//Game Logic
		Player1.Logic(Scene.GetMap());
		Player2.Logic(Scene.GetMap());
		DetectCollisions();

		
	}
	return res;
}

	

void cGame::glutPrint(float x, float y, LPVOID font, std::string text)
{
	glRasterPos2f(x, y);

	for (int i = 0; i<text.size(); i++)
	{
		glutBitmapCharacter(font, text[i]);
	}
}

void cGame::glutPrint(float x, float y, LPVOID font, std::string text, float red, float green, float blue)
{
	//if (!text || !strlen(text)) return;
	bool blending = false;
	if (glIsEnabled(GL_BLEND)) blending = true;
	glEnable(GL_BLEND);
	glColor3f(red, green, blue);
	glRasterPos2f(x, y);
	for (int i = 0; i<text.size(); i++) {
		glutBitmapCharacter(font, text[i]);
		
	}
	if (!blending) glDisable(GL_BLEND);
	
}
void cGame::DrawIntro(){
	glEnable(GL_TEXTURE_2D);
	

	
	glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_LOGO));
	



	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);	glVertex2i((GAME_WIDTH / 2) - 256, (GAME_HEIGHT / 2) - 180);
	glTexCoord2f(1.0f, 1.0f);	glVertex2i((GAME_WIDTH / 2) - 256 + 512, (GAME_HEIGHT / 2) - 180);
	glTexCoord2f(1.0f, 0.0f);	glVertex2i((GAME_WIDTH / 2) - 256 + 512, (GAME_HEIGHT / 2) - 180 + 360);
	glTexCoord2f(0.0f, 0.0f);	glVertex2i((GAME_WIDTH / 2) - 256, (GAME_HEIGHT / 2) - 180 + 360);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glutPrint((GAME_WIDTH / 2)-70, (GAME_HEIGHT / 2)-200, GLUT_BITMAP_HELVETICA_18, "PRESS ENTER");
	glLoadIdentity();
	glutSwapBuffers();
	
}

void cGame::DrawHUD(){

	glutPrint(0, (GAME_HEIGHT-20), GLUT_BITMAP_HELVETICA_18, "Player1");
	glutPrint((GAME_WIDTH - 70), (GAME_HEIGHT - 20), GLUT_BITMAP_HELVETICA_18, "Player2");
	glutPrint((GAME_WIDTH / 2), (GAME_HEIGHT - 20), GLUT_BITMAP_HELVETICA_18, "TIME:");
	glutPrint((GAME_WIDTH / 2), (GAME_HEIGHT - 20)-20, GLUT_BITMAP_HELVETICA_18, "   99");

	//------ HEART PLAYER1 ------//
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_HEART));
	glBegin(GL_QUADS);

	glTexCoord2f(0.25f, 0.0f);	glVertex2i(0, (GAME_HEIGHT - 40));
	glTexCoord2f(0.5f, 0.0f);	glVertex2i(0 + 24, (GAME_HEIGHT - 40));
	glTexCoord2f(0.5f, 1.0f);	glVertex2i(0 + 24, (GAME_HEIGHT - 40) - 24);
	glTexCoord2f(0.25f, 1.0f);	glVertex2i(0, (GAME_HEIGHT - 40) - 24);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glutPrint(0 + 24, (GAME_HEIGHT - 40) - 20, GLUT_BITMAP_HELVETICA_18, "X " + Player1.MostrarVidas());


	//------ HEART PLAYER2 ------//
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_HEART));
	glBegin(GL_QUADS);

	glTexCoord2f(0.25f, 0.0f);	glVertex2i((GAME_WIDTH - 70), (GAME_HEIGHT - 40));
	glTexCoord2f(0.5f, 0.0f);	glVertex2i((GAME_WIDTH - 70) + 24, (GAME_HEIGHT - 40));
	glTexCoord2f(0.5f, 1.0f);	glVertex2i((GAME_WIDTH - 70) + 24, (GAME_HEIGHT - 40) - 24);
	glTexCoord2f(0.25f, 1.0f);	glVertex2i((GAME_WIDTH - 70), (GAME_HEIGHT - 40) - 24);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glutPrint((GAME_WIDTH - 70) + 24, (GAME_HEIGHT - 40) - 20, GLUT_BITMAP_HELVETICA_18, "X " + Player2.MostrarVidas());
	
	glLoadIdentity();
	//glutSwapBuffers();

}
//Game output
void cGame::Render()
{
	int tex_w, tex_h;
	int tex_w2, tex_h2;
	glClear(GL_COLOR_BUFFER_BIT);
	


	if (state == STATE_INTRO){
		Scene.Draw(Data.GetID(IMG_BLOCKS));

	
	
		
		DrawIntro();

	}else if (state == STATE_RUN){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();

		Scene.Draw(Data.GetID(IMG_BLOCKS));
		DrawHUD();
		Player1.Draw(Data.GetID(IMG_PLAYER1));
		Player2.Draw(Data.GetID(IMG_PLAYER2));

		int x, y;
		Data.GetSize(IMG_HEART, &tex_w, &tex_h);
		std::list<cItem*>::iterator it_t;


		for (it_t = items.begin(); it_t != items.end(); it_t++)
		{
			x = (*it_t)->GetX();
			y = (*it_t)->GetY();

			if (static_cast<cHeart*>(*it_t) != NULL) //verificamos a que subclase pertenece el puntero
			{
				
				(*it_t)->Draw(Data.GetID(IMG_HEART), x, y, tex_w, tex_h, true);
			}


		}
		Data.GetSize(IMG_ITEMS, &tex_w, &tex_h);
		std::list<cItem*>::iterator it_to;


		for (it_to = toads.begin(); it_to != toads.end(); it_to++)
		{
			x = (*it_to)->GetX();
			y = (*it_to)->GetY();

			if (static_cast<cToad*>(*it_to) != NULL) //verificamos a que subclase pertenece el puntero
			{
			
				(*it_to)->DrawToad(Data.GetID(IMG_ITEMS), x, y, tex_w, tex_h, true);
			}


		}

		Data.GetSize(IMG_ITEMS, &tex_w, &tex_h);
		std::list<cDisparo*>::iterator it_td;


		for (it_td = shoots.begin(); it_td != shoots.end(); it_td++)
		{
			x = (*it_td)->GetX();
			y = (*it_td)->GetY();

			if (static_cast<cDisparo*>(*it_td) != NULL) //verificamos a que subclase pertenece el puntero
			{

				(*it_td)->Draw(Data.GetID(IMG_ITEMS), tex_w, tex_h, true, Scene.GetMap());
			}


		}

		Data.GetSize(IMG_ITEMS, &tex_w, &tex_h);
		std::list<cEnemy*>::iterator it_ts;


		for (it_ts = spines.begin(); it_ts != spines.end(); it_ts++)
		{
			x = (*it_ts)->GetX();
			y = (*it_ts)->GetY();

			if (static_cast<cEnemy2*>(*it_ts) != NULL) //verificamos a que subclase pertenece el puntero
			{
			
				(*it_ts)->DrawSpine(Data.GetID(IMG_ITEMS), tex_w, tex_h, true, Scene.GetMap());
			}


		}

		Data.GetSize(IMG_ENEMY, &tex_w, &tex_h);
		std::list<cEnemy*>::iterator it_e;
		for (it_e = shells.begin(); it_e != shells.end(); it_e++)
		{
			x = (*it_e)->GetX();
			y = (*it_e)->GetY();

			if (static_cast<cEnemy*>(*it_e) != NULL) //verificamos a que subclase pertenece el puntero
			{

				//(*it_e)->SetPosition(x, y);
				//(*it_e)->SetState(WALKLEFT);
				(*it_e)->Draw(Data.GetID(IMG_ENEMY), tex_w, tex_h, true, Scene.GetMap());

			}
		}



		glutSwapBuffers();
	}
	else if (state == STATE_GAMEOVER){
		int t_id;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glutPrint((GAME_WIDTH / 2) - 24, (GAME_HEIGHT / 2) - 20, GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER");
		if(Player1.vidas > Player2.vidas){

			glutPrint((GAME_WIDTH / 2) - 24, (GAME_HEIGHT / 2) - 40, GLUT_BITMAP_HELVETICA_18, "Player 1 Wins!!!!");
			t_id = Data.GetID(IMG_PLAYER1);
			Player1.SetTile(36, 15);
			Player1.SetWidthHeight(96, 96);
			Player1.Draw(Data.GetID(IMG_PLAYER1));

		}
		else{
			glutPrint((GAME_WIDTH / 2) - 24, (GAME_HEIGHT / 2) - 40, GLUT_BITMAP_HELVETICA_18, "Player 2 Wins!!!!");
			Player2.SetTile(36, 15);
			Player2.SetWidthHeight(96, 96);
			Player2.Draw(Data.GetID(IMG_PLAYER2));
		}


		glLoadIdentity();

		glutSwapBuffers();
	}
}
