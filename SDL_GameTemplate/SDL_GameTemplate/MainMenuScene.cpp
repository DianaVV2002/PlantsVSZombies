#include "MainMenuScene.h"
#include <iostream>
#include <SDL_image.h>

MainMenuScene::MainMenuScene(SDL_Renderer* renderer, Game* game)
{
	this->renderer = renderer;
	this->game = game;
}
void MainMenuScene::init()
{

	SDL_Rect src, dest;
	src.h = 128;
	src.w = 128;
	src.x = 0;
	src.y = 0;
	dest.w = 128;
	dest.h = 128;
	dest.x = width / 2 - dest.w/2 ;
	dest.y = height / 4 - dest.h ;
	plants = new Button("assets/plantsvs.png", renderer, src, dest);
	src.h = 96;
	src.w = 96;
	dest.w = 96;
	dest.h = 96;
	dest.y = height / 4 - dest.h/20;
	easy = new Button("assets/easy.png", renderer, src, dest);
	std::cout << easy;
	dest.y += dest.h;
	medium=new Button("assets/medium.png", renderer, src, dest);
	src.h = src.w = 32;

	dest.w = dest.h;
	dest.y += dest.h;
	hard = new Button("assets/hard.png", renderer, src, dest);
	dest.y += dest.h;
	exit = new Button("assets/exit.png", renderer, src, dest);
	
			
}

void MainMenuScene::update()
{
	std::cout << "Update main menu\n";
}

void MainMenuScene::draw()
{
	SDL_RenderClear(renderer);
	easy->Render();
	medium->Render();
	hard->Render();
	exit->Render();
	plants->Render();
	SDL_RenderPresent(renderer);
	
}
void MainMenuScene::handleEvents(SDL_Event& event)
{
	play1 = false;
	play2 = false;
	play3 = false;
	playExit = false;

	SDL_GetMouseState(&Mx, &My);
	if (easy->InsideButton(Mx,My))
	{
		SDL_SetTextureColorMod(levelEasy, 250, 0, 0);

		if (event.type == SDL_MOUSEBUTTONDOWN)  
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{    //if it is pressed then play1 becomes true which you could use to initiate the newgame
				play1 = true;
			}
			
		}
		
	}
	if (medium->InsideButton(Mx,My))
	{
		SDL_SetTextureColorMod(levelMedium, 250, 0, 0);

		if (event.type == SDL_MOUSEBUTTONDOWN)  
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{    //if it is pressed then play1 becomes true which you could use to initiate the newgame
				play2 = true;
			}
		}
	}
	if (hard->InsideButton(Mx,My))
	{
		SDL_SetTextureColorMod(levelHard, 250, 0, 0);

		if (event.type == SDL_MOUSEBUTTONDOWN)  //this calls an event, I assume that you already know how to make an event right? 
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{    //if it is pressed then play1 becomes true which you could use to initiate the newgame
				play3 = true;
			}
		}
	}
	if (exit->InsideButton(Mx,My))
	{
		SDL_SetTextureColorMod(exitButton, 250, 0, 0);

		if (event.type == SDL_MOUSEBUTTONDOWN)  //this calls an event, I assume that you already know how to make an event right? 
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{    //if it is pressed then play1 becomes true which you could use to initiate the newgame
				playExit = true;
			}
		}
	}
	if (play1)
	{ 
		Level1Scene* scene = new Level1Scene(renderer,game);
		scene->init();
		game->setScene(scene);
		
	}
	if (play2)
	{
		Level2Scene* scene = new Level2Scene(renderer, game);
		scene->init();
		game->setScene(scene);
		
	}
	if (play3)
	{
		Level3Scene* scene = new Level3Scene(renderer, game);
		scene->init();
		game->setScene(scene);
		
	}
	if (playExit)
	{
		delete game;
	}

}

MainMenuScene::~MainMenuScene()
{

}
SDL_Surface* MainMenuScene:: loadSurface(const char* path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	try
	{

		//Load image at specified path
		std::cout << "inainte image load\n";
		SDL_Surface* background = IMG_Load(path);
		std::cout << "dupa image load\n";
		if (background == NULL)
		{
			std::cout << "dupa image load2\n";
			std::cout << "Unable to load image %s! SDL_image Error: %s\n";
		}
		else
		{
			
			//Convert surface to screen format
			optimizedSurface = SDL_ConvertSurface(background, ScreenSurface->format, 0);
			if (optimizedSurface == NULL)
			{
				printf("Unable to optimize image %s! SDL Error: %s\n");
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(background);
		}
	}
	catch(...)
	{
		std::cout << "Mare exceptie\n";
	}
	

	return optimizedSurface;
}