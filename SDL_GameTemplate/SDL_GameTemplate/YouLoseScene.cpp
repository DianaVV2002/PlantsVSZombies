#include "YouLoseScene.h"

YouLoseScene::YouLoseScene(SDL_Renderer* renderer, Game* game)
{
	this->renderer = renderer;
	this->game = game;

}
void YouLoseScene::init()
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
	dest.y -= dest.h;
	replayLevel = new Button("assets/replay.png", renderer, src, dest);
	dest.y -= dest.h;
	loser = new Button("assets/loser.png", renderer, src, dest);

}
void YouLoseScene::update()
{

}
void YouLoseScene::draw()
{
	SDL_RenderClear(renderer);
	backMain->Render();
	replayLevel->Render();
	loser->Render();

	SDL_RenderPresent(renderer);
}
void YouLoseScene::handleEvents(SDL_Event& event)
{

	bool playBack = false;
	bool playReplayLevel = false;

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
	if (replayLevel->InsideButton(Mx, My))
	{
		SDL_SetTextureColorMod(replayLevelTex, 250, 0, 0);

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{    //if it is pressed then play1 becomes true which you could use to initiate the newgame
				playReplayLevel = true;
			}

		}

	}
	
	if (playBack)
	{
		MainMenuScene* scene = new MainMenuScene(renderer, game);
		scene->init();
		game->setScene(scene);
	}
	if (playReplayLevel)
	{
		int lvl;
		ifstream fileLevel("assets/Levels.txt");
		fileLevel >> lvl;
		if (lvl == 1)
		{
			Level1Scene* scene = new Level1Scene(renderer, game);
			scene->init();
			game->setScene(scene);
		}

		if (lvl == 2)
		{
			Level2Scene* scene = new Level2Scene(renderer, game);
			scene->init();
			game->setScene(scene);
		}
		if (lvl == 3)
		{
			Level3Scene* scene = new Level3Scene(renderer, game);
			scene->init();
			game->setScene(scene);
		}

		fileLevel.close();
	}
}
