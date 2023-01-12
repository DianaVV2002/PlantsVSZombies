#pragma once
#include "SDL.h"
/// <summary>
/// Base class for each component 
/// </summary>

enum KEY_p { UP, RIGHT, DOWN, LEFT, DEFAULT };

class Component
{
public:
	virtual ~Component() = default;
	virtual void init(int x, int y) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual bool checkCollision(const SDL_Rect& r) = 0;
};