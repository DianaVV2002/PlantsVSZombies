#pragma once
#include "Scene.h"


class Level2Scene :public Scene
{
public:
	Level2Scene(SDL_Renderer* renderer, Game* game);
	void init();
	void update();
	void draw();
	void handleEvents(SDL_Event& event);
	~Level2Scene() = default;
};