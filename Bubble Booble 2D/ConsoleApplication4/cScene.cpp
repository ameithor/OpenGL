#include "cScene.h"
#include "Globals.h"


using namespace std;
cScene::cScene()
{
}


cScene::~cScene()
{
}
bool cScene::LoadLevel(int level)
{
	bool res;
	FILE *fd;
	char file[32];
	int i, j, px, py;
	char tile;
	float coordx_tile, coordy_tile;

	res = true;

	if (level<10) sprintf(file, "Levels/%s0%d%s", (char *)FILENAME_LEVEL, level, (char *)FILENAME_EXT);
	else		 sprintf(file, "Levels/%s%d%s", (char *)FILENAME_LEVEL, level, (char *)FILENAME_EXT);

	fd = fopen(file, "r");
	if (fd == NULL) return false;

	id_DL = glGenLists(1);
	glNewList(id_DL, GL_COMPILE);
	glBegin(GL_QUADS);

	for (j = SCENE_HEIGHT - 1; j >= 0; j--)
	{
		px = SCENE_Xo;
		//py = SCENE_Yo + (j*TILE_SIZE);
		py = SCENE_Yo + (j*TILE_SIZE);

		for (i = 0; i<SCENE_WIDTH; i++)
		{
			
			fscanf(fd, "%c", &tile);
			//std::cout << " tile " << j << "-" << i<< "-->" << tile << "\n";
			if (tile == ' ')
			{
				//Tiles must be != 0 !!!
				map[(j*SCENE_WIDTH) + i] = 0;
			}
			else
			{
				//Tiles = 1,2,3,...
				map[(j*SCENE_WIDTH) + i] = tile - 48;
				//cout << "j:" << j << "i:" << i << "->" << tile << " ";



			if (map[(j*SCENE_WIDTH) + i] == 1){ coordx_tile = 0.0f; coordy_tile = 0.0f; } //Bloque naranja
				if (map[(j*SCENE_WIDTH) + i] == 2){ coordx_tile = 0.5f; coordy_tile = 0.0f; } //Bloque azul
				if (map[(j*SCENE_WIDTH) + i] == 3){ coordx_tile = 0.0f; coordy_tile = 0.5f; } //Bloque rojo
				if (map[(j*SCENE_WIDTH) + i] == 4){ coordx_tile = 0.5f; coordy_tile = 0.5f; } //Bloque verde
				
				
				

				//BLOCK_SIZE = 24, FILE_SIZE = 64
				// 24 / 64 = 0.375
				glTexCoord2f(coordx_tile, coordy_tile + 0.375f);	glVertex2i(px, py);
				glTexCoord2f(coordx_tile + 0.375f, coordy_tile + 0.375f);	glVertex2i(px + BLOCK_SIZE, py);
				glTexCoord2f(coordx_tile + 0.375f, coordy_tile);	glVertex2i(px + BLOCK_SIZE, py + BLOCK_SIZE);
				glTexCoord2f(coordx_tile, coordy_tile);	glVertex2i(px, py + BLOCK_SIZE);

			}
			px += TILE_SIZE;
			
		}
		cout << "\n" << "\n";
		fscanf(fd, "%c", &tile); //pass enter
	}

	glEnd();
	glEndList();

	fclose(fd);

	return res;
}

bool cScene::LoadItems(int level)
{
	bool res;/*
	FILE *fd;
	char file[16];
	int i, j, px, py;
	char tile;
	float coordx_tile, coordy_tile;

	res = true;

	if (level<10) sprintf(file, "Levels/%s0%d%s", (char *)FILENAME_ITEMS, level, (char *)FILENAME_EXT);
	else		 sprintf(file, "Levels/%s%d%s", (char *)FILENAME_ITEMS, level, (char *)FILENAME_EXT);

	fd = fopen(file, "r");
	if (fd == NULL) return false;

	id_items = glGenLists(1);
	glNewList(id_items, GL_COMPILE);
	glBegin(GL_QUADS);

	for (j = SCENE_HEIGHT - 1; j >= 0; j--)
	{
		px = SCENE_Xo;
		py = SCENE_Yo + (j*TILE_SIZE);

		for (i = 0; i<SCENE_WIDTH; i++)
		{

			fscanf(fd, "%c", &tile);
			if (tile == '5')
			{
				//Tiles = 1,2,3,...
				map[(j*SCENE_WIDTH) + i] = tile - 48;
				cout << "j:" << j << "i:" << i << "->" << tile << " ";



				if (map[(j*SCENE_WIDTH) + i] == 5){ coordx_tile = 0.0f; coordy_tile = 0.0f; } //Bloque naranja
				if (map[(j*SCENE_WIDTH) + i] == 6){ coordx_tile = 0.25f; coordy_tile = 0.0f; } //Bloque azul
				if (map[(j*SCENE_WIDTH) + i] == 7){ coordx_tile = 0.50f; coordy_tile = 0.0f; } //Bloque rojo
				if (map[(j*SCENE_WIDTH) + i] == 8){ coordx_tile = 0.75f; coordy_tile = 0.0f; } //Bloque verde
				

				
			
				//BLOCK_SIZE = 24, FILE_SIZE = 64
				// 24 / 64 = 0.375
				glTexCoord2f(coordx_tile, coordy_tile + 0.375f);	glVertex2i(px, py);
				glTexCoord2f(coordx_tile + 0.375f, coordy_tile + 0.375f);	glVertex2i(px + HEART_SIZE, py);
				glTexCoord2f(coordx_tile + 0.375f, coordy_tile);	glVertex2i(px + HEART_SIZE, py + HEART_SIZE);
				glTexCoord2f(coordx_tile, coordy_tile);	glVertex2i(px, py + HEART_SIZE);
			}
			else{
				map[(j*SCENE_WIDTH) + i] = 0;
			}
			px += TILE_SIZE;

		}
		cout << "\n" << "\n";
		fscanf(fd, "%c", &tile); //pass enter
	}

	glEnd();
	glEndList();

	fclose(fd);

	*/
	return true;
}

void cScene::Draw(int tex_id)
{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glCallList(id_DL);
	//glCallList(id_items);
	glDisable(GL_TEXTURE_2D);
}

void cScene::DrawAnimatedTiles(int tex_id, int tex_w, int tex_h)
{
/*	unsigned int i;
	int px, py;
	float coordx_tile, coordy_tile;
	float tex_offset_x, tex_offset_y;

	tex_offset_x = 1.0f / float(tex_w / TEXTURE_TILE_SIZE);
	tex_offset_y = 1.0f / float(tex_h / TEXTURE_TILE_SIZE);

	for (i = 0; i<animated_tiles.size(); i++)
	{
		px = animated_tiles[i].GetX();
		py = animated_tiles[i].GetY();
		coordx_tile = animated_tiles[i].GetTexCoordX();
		coordy_tile = animated_tiles[i].GetTexCoordY();

		glBegin(GL_QUADS);

		glTexCoord2f(coordx_tile + tex_offset_x*seq, coordy_tile + tex_offset_y);	glVertex3i(px, py, (SCENE_HEIGHT*TILE_SIZE) + 2);
		glTexCoord2f(coordx_tile + tex_offset_x*(seq + 1), coordy_tile + tex_offset_y);	glVertex3i(px + TILE_SIZE, py, (SCENE_HEIGHT*TILE_SIZE) + 2);
		glTexCoord2f(coordx_tile + tex_offset_x*(seq + 1), coordy_tile);					glVertex3i(px + TILE_SIZE, py + TILE_SIZE, (SCENE_HEIGHT*TILE_SIZE) + 2);
		glTexCoord2f(coordx_tile + tex_offset_x*seq, coordy_tile);					glVertex3i(px, py + TILE_SIZE, (SCENE_HEIGHT*TILE_SIZE) + 2);

		glEnd();
	}
	for (i = 0; i<animated_tiles_up.size(); i++)
	{
		px = animated_tiles_up[i].GetX();
		py = animated_tiles_up[i].GetY();
		coordx_tile = animated_tiles_up[i].GetTexCoordX();
		coordy_tile = animated_tiles_up[i].GetTexCoordY();

		glBegin(GL_QUADS);

		glTexCoord2f(coordx_tile + tex_offset_x*seq, coordy_tile + tex_offset_y);	glVertex3i(px, py, 0);
		glTexCoord2f(coordx_tile + tex_offset_x*(seq + 1), coordy_tile + tex_offset_y);	glVertex3i(px + TILE_SIZE, py, 0);
		glTexCoord2f(coordx_tile + tex_offset_x*(seq + 1), coordy_tile);					glVertex3i(px + TILE_SIZE, py + TILE_SIZE, 0);
		glTexCoord2f(coordx_tile + tex_offset_x*seq, coordy_tile);					glVertex3i(px, py + TILE_SIZE, 0);

		glEnd();
	}*/
}
int* cScene::GetMap()
{
	return map;
}
