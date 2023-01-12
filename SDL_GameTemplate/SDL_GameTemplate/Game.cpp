#include "Game.h"
#include <iostream>
#include "Map.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Health.h"
#include "MainMenuScene.h"
#include "Level1Scene.h"

Game::Game(): isRunning(false), window(nullptr), renderer(nullptr)
{
}

Game::~Game()
{
   
}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized" << std::endl;
		auto window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window!=nullptr)
		{
			std::cout << "Window created" << std::endl;
		}
 
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer != nullptr)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	SDL_Rect src, dest;
	src.h = 0;
	src.w = 0;
	src.x = 0;
	src.y = 0;


	dest.w = width / 3;
	dest.h = height / 5;
	dest.x = width / 2 - dest.w / 2;
	dest.y = height / 4 - dest.h / 2;


	scene = new MainMenuScene(renderer, this);
	scene->init();
	this->setScene(scene);
}
void Game::setScene(Scene* scene)
{
	this->scene = scene;
}
void Game::handleEvents()
{

	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT: {
		
		isRunning = false;
		break;
	}
	default:
		scene->handleEvents(event);
		break;
	}
	
}
//obiecte care se actualizeaza(bullet, life)
void Game::update() const
{
	scene->update();
}

//obiecte de afisat
void Game::render() const
{
	scene->draw();
}

void Game::clean() const
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_QUIT;
	std::cout << "Game cleaned" << std::endl;
}
Scene* Game::getScene()
{
	return scene;
}