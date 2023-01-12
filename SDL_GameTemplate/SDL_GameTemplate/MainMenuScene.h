#pragma once
#include "Scene.h"
#include "SDL.h"
#include "TextureManager.h"
#include"Level1Scene.h"
#include"Level2Scene.h"
#include "Level3Scene.h"
class Button;
#include "Button.h"

class MainMenuScene :public Scene
{
	//The surface contained by the window
	SDL_Surface* ScreenSurface = NULL;
	//The image we will load and show on the screen
	SDL_Surface* background = NULL;
	SDL_Texture* exitButton;
	SDL_Texture* levelEasy;
	SDL_Texture* levelMedium;
	SDL_Texture* levelHard;
	SDL_Texture* plantsTex;
	Button* plants;
	Button* easy;
	Button* medium;
	Button* hard;
	Button* exit;
	Game* game;
	bool play1,play2,play3,playExit;
	int Mx = 0;//coord mouse
	int My = 0;

public:
	MainMenuScene(SDL_Renderer* renderer,Game* game);
	void init();
	void update();
	void draw();
	void setTex();
	SDL_Surface* loadSurface(const char* path);
	void handleEvents(SDL_Event& event);
	~MainMenuScene();

};