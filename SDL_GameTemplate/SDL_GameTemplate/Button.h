#pragma once
#include "GameObject.h"
#include "TextureManager.h"

class Button : public GameObject
{
public:
	Button(const char* textureImage, SDL_Renderer* renderer, SDL_Rect _srcrec, SDL_Rect _destrec);
	void Render();
	bool InsideButton( int x, int y);
	~Button()=default;
private:
	SDL_Texture* texture;
	SDL_Rect srcrec, destrec;
	SDL_Renderer* renderer;
};