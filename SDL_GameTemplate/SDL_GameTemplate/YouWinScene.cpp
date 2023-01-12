#include "YouWinScene.h"

YouWinScene::YouWinScene(SDL_Renderer* renderer, Game* game)
{
	this->renderer = renderer;
	this->game = game;

}
void YouWinScene::init()
{
	SDL_Rect src, dest;
	src.h = 96;
	src.w = 96;
	src.x = 0;
	src.y = 0;
	dest.w = 96;
	dest.h = 96;
	dest.y = dest.h;
	dest.x = width / 2 - dest.w / 2;
	dest.y += 4 * dest.h;
	backMain = new Button("assets/backToMainMenu.png", renderer, src, dest);
	dest.y -=  dest.h;
	nextLevel= new Button("assets/nextLevel2.png", renderer, src, dest);
	dest.y -= dest.h;
	winner= new Button("assets/winner.png", renderer, src, dest);

}
void YouWinScene::update()
{

}
void YouWinScene::draw()
{
	SDL_RenderClear(renderer);
	backMain->Render();
	nextLevel->Render();
	winner->Render();
	std::cout << "you win draw";

	SDL_RenderPresent(renderer);
}
void YouWinScene::handleEvents(SDL_Event& event)
{

	bool playBack = false;
	bool playNext = false;

	SDL_GetMouseState(&Mx, &My);
	if (backMain->InsideButton(Mx, My))
	{
		SDL_SetTextureColorMod(backMainTex, 250, 0, 0);

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{    //if it is pressed then play1 becomes true which you could use to initiate the newgame
				playBack = true;
			}

		}

	}
	if (nextLevel->InsideButton(Mx, My))
	{
		SDL_SetTextureColorMod(nextLevelTex, 250, 0, 0);

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{    //if it is pressed then play1 becomes true which you could use to initiate the newgame
				playNext = true;
			}

		}

	}
	std::cout << "you win handle\n";
	if (playBack)
	{
		MainMenuScene* scene = new MainMenuScene(renderer, game);
		scene->init();
		game->setScene(scene);
	}
	if (playNext)
	{
		int lvl;
		ifstream fileLevel("assets/Levels.txt");
		fileLevel >> lvl;
			if (lvl == 1)
			{
				Level2Scene* scene = new Level2Scene(renderer, game);
				scene->init();
				game->setScene(scene);
			}
	
			if (lvl == 2)
			{
				Level3Scene* scene = new Level3Scene(renderer, game);
				scene->init();
				game->setScene(scene);
			}
			if (lvl == 3)
			{
				MainMenuScene* scene = new MainMenuScene(renderer, game);
				scene->init();
				game->setScene(scene);
			}

			fileLevel.close();
	}
}
