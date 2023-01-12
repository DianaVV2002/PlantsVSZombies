#pragma once
#include "SDL.h"
#include "Scene.h"
#include "TextureManager.h"
#include "Game.h"
#include"MainMenuScene.h"
class Game;
class Button;
#include "Button.h"
#include<fstream>
#include <iostream>
using std::ifstream;

class YouWinScene:public Scene
{
	Button* backMain;
	Button* nextLevel;
	Button* winner;
	SDL_Texture* backMainTex;
	SDL_Texture* nextLevelTex;
	SDL_Texture* winnerTex;
	SDL_Renderer* renderer;
	Game* game;
	int Mx = 0;//coord mouse
	int My = 0;
public:
	YouWinScene(SDL_Renderer* renderer,  Game* game);
	void init();
	void update();
	void draw();
	void handleEvents(SDL_Event& event);
	~YouWinScene() = default;

};