#include "Level1Scene.h"
#include "Map.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Health.h"
#include "MainMenuScene.h"
#include <iostream>
#include "YouWinScene.h"
#include "YouLoseScene.h"
#include<iostream>
#include<fstream>
using std::ofstream;

Map* map;

Player* player;

EnemyManager* enemyManager;

BulletManager* bulletManager;

Health* health;

Level1Scene::Level1Scene(SDL_Renderer* renderer, Game* game)
{
	this->renderer = renderer;
	this->game = game;
}
	
void Level1Scene::init()
{
	int lvl = 1;
	map = new Map(renderer);

	player = new Player("assets/plantPlayer.png", renderer);
	player->setMap(map);
	player->init(32, 32);

	std::cout << "Player initializat\n";
	health = new Health("assets/health.png", renderer);
	health->setPlayer(player);
	health->init(0, 0);

	bulletManager = new BulletManager("assets/bullet.png", renderer);
	bulletManager->setMap(map);
	std::cout << "Bullet manager initializat\n";
	player->setBulletManager(bulletManager);

	enemyManager = new EnemyManager("assets/zombie.png", renderer);
	enemyManager->setMap(map);
	enemyManager->setBulletManager(bulletManager);
	enemyManager->init(lvl, player);

	std::cout << "Enemy manager initializat\n";
}

void Level1Scene::update()
{
	if (player->isAlive())
		player->update();
	else
	{
		player->setTex("assets/deadPlayer.png");
		ofstream fileLevel("assets/Levels.txt");
		fileLevel << 1;
		Scene* scene = new YouLoseScene(renderer, game);
		scene->init();
		game->setScene(scene);
		fileLevel.close();
	}
	//std::cout << "Player update\n";
	health->update();
	//std::cout << "Health update\n";
	if(enemyManager->getNumberEnemies())
	enemyManager->update();
	else
	{
		if (player->isAlive())
			//lucru cu fisiere
		{
			ofstream fileLevel("assets/Levels.txt");
				
				fileLevel << 1;
				Scene* scene = new YouWinScene(renderer, game); //polimorfism clasa scene parinte
				scene->init();
				game->setScene(scene);
				fileLevel.close();
		
		}
	}
	//std::cout << "Enemy manager update\n";
	bulletManager->update();
	//std::cout << "Bullet manager update\n";
	//std::cout <<  player->getPlayerPos().x<<" "<< player->getPlayerPos().y << '\n';
}

void Level1Scene::draw()
{
	SDL_RenderClear(renderer);
	// this is where we would add stuff to render
	map->DrawMap();
	player->draw();
	health->draw();
	if (enemyManager->getNumberEnemies())
	enemyManager->draw();
	bulletManager->draw();
	//std::cout << "DESEN\n";
	SDL_RenderPresent(renderer);
}

void Level1Scene::handleEvents(SDL_Event& event)
{
	switch (event.key.keysym.sym)
	{
		case SDLK_ESCAPE:
		{
			Scene* scene = new MainMenuScene(renderer, game);
			scene->init();
			game->setScene(scene);
		}
		break;

		default:
			player->handleEvent(event);
			break;
	}
}