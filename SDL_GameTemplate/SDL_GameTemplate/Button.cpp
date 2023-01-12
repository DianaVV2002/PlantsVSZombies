#include"Button.h"
#include <iostream>
Button::Button(const char* textureImage, SDL_Renderer* renderer, SDL_Rect srcrec, SDL_Rect destrec)
{
	this->texture = TextureManager::LoadTexture(textureImage, renderer);
	this->renderer = renderer;
	this->srcrec = srcrec;
	this->destrec = destrec;
};

void Button::Render()
{
	std::cout << "SUNT BUTON SI MA DESENEZ la coordonatele: " << destrec.x << " " << destrec.y << '\n';
	TextureManager::Draw(texture, srcrec, destrec, renderer);
}

bool Button::InsideButton(int x, int y)
{
	if (x > destrec.x && x < destrec.x + destrec.w && y > destrec.y && y < destrec.y + destrec.h)
		return 1;
	return 0;
}