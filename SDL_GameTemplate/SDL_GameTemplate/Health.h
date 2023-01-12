#pragma once
#include "SDL.h"
#include "TextureManager.h"
#include "Player.h"

class Health
{
	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	SDL_Rect srcRect{}, destRect{};
	Player* player;
	int health;
public:
	Health() = default;
	Health(const char* path, SDL_Renderer* renderer);

	void setTex(const char* path);

	void init(int x, int y) ;

	void update() ;//aici se face miscarea

	void draw() ;//dese\

	void setPlayer(Player* player);

};