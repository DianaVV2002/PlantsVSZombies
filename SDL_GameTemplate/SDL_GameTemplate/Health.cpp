#include "Health.h"
#include <iostream>

Health::Health(const char* path, SDL_Renderer * renderer) : renderer(renderer)
{
	setTex(path);
}

void Health::setTex(const char* path)
{
	texture = TextureManager::LoadTexture(path, renderer);
}

void Health::init(int x, int y)
{
	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 32;
	destRect.w = destRect.h = 32;
	destRect.x = x;
	destRect.y = y;
	health = 3;
}

void Health::update()
{
	
	health = player->getHealth();
}

void Health::draw()
{
	
	SDL_Rect** destRects = new SDL_Rect*[health];
	for (int i = 0; i < health; i++)
	{
		destRects[i] = new SDL_Rect{ destRect.x + i *32, destRect.y, destRect.w, destRect.h };
	}

	for (int i = 0; i < health; i++)
	{
		TextureManager::Draw(texture, srcRect, *destRects[i], renderer);
	}

	for (int i = 0; i < health; i++)
		delete destRects[i];
	delete[] destRects;
}
void Health::setPlayer(Player* player)
{
	this->player = player;
}
