#include "Map.h"
#include "TextureManager.h"
#include <SDL.h>

using namespace std;

/*
int lvl1[20][25] = {
	{0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
*/
Map::Map(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	grass = TextureManager::LoadTexture("assets/grass.png", renderer);
	wall= TextureManager::LoadTexture("assets/wall.png", renderer);
	tree= TextureManager::LoadTexture("assets/tree.png", renderer);
	flowers = TextureManager::LoadTexture("assets/flowers.png", renderer);
	LoadMap((char*)"assets/Map1.txt");

	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;
	dest.x = 0;
	dest.y = 0;
	dest.w = 32;
	dest.h = 32;

}

Map::~Map()
{

}

void Map::LoadMap(char* filePath)
{
	// Fisier
	// Exceptie
	ifstream file;
	try
	{
		file.open(filePath);
		if (!file)
			throw "Nu exista fisierul pentru harta/n";

	}
	catch(const char* err)
	{
		cout << err;
	}

	file >> lin >> col;

	map = new int* [lin];
	for (int i = 0; i < lin; ++i)
		map[i] = new int[col];

	for (int row = 0; row < lin; row++)
	{
		for (int column = 0; column < col; column++)
		{
			file >> map[row][column];
		}
	}

	file.close();
}

void Map::DrawMap()
{
	int type = 0;
	for (int row = 0; row < lin; row++)
	{
		for (int column = 0; column < col; column++)
		{
			type = map[row][column];

			dest.x = column * 32;
			dest.y = row * 32;
			switch (type)
			{
			
			case 0:
			{
				TextureManager::Draw(grass, src, dest, renderer);
				break;
			}
			case 1:
			{
				TextureManager::Draw(wall, src, dest, renderer);
				break;
			}
			case 2:
				TextureManager::Draw(flowers, src, dest, renderer);
				break;
			default:
				break;
			}
		}
	}
}

int Map::GetLin()
{
	return lin;
}

int Map::GetCol()
{
	return col;
}

int** Map::GetMap()
{
	return map;
}

SDL_Rect convertTileToRect(int x, int y, int w, int h)
{
	return SDL_Rect{ x, y, w, h };
}