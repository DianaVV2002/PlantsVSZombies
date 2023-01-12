#pragma once
#include <fstream>
#include <iostream>
#include <SDL_image.h>

SDL_Rect convertTileToRect(int x, int y, int w, int h);

class Map
{
public:
	Map(SDL_Renderer* renderer);
	~Map();

	void LoadMap(char* filePath);
	void DrawMap();
	int GetLin();
	int GetCol();
	int** GetMap();

private:
	SDL_Renderer* renderer;
	SDL_Rect src, dest;
	SDL_Texture* grass;
	SDL_Texture* wall;
	SDL_Texture* tree;
	SDL_Texture* flowers;

	int** map;
	int lin;
	int col;
};
