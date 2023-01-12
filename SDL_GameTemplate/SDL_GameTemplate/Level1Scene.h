#pragma once
#include "Scene.h"


class Level1Scene :public Scene
{
public:
	Level1Scene(SDL_Renderer* renderer, Game* game);
	void init();
	void update();
	void draw();
	void handleEvents(SDL_Event& event);
	~Level1Scene() = default;
};