#pragma once
#include "Scene.h"
//3 nivele

class Level3Scene :public Scene
{
public:
	Level3Scene(SDL_Renderer* renderer, Game* game);
	void init();
	void update();
	void draw();
	void handleEvents(SDL_Event& event);
	~Level3Scene() = default;
};