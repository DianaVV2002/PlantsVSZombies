#pragma once
class Game;
#include "SDL.h"
#include "Game.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;
//interfata
class Scene
{
protected:

	SDL_Renderer* renderer;
	Game* game;
	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGHT;
public:

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void handleEvents(SDL_Event& event) = 0;
	virtual ~Scene() = default;
};
