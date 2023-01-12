class Enemy;
#include "Level2Scene.h"
class YouWinScene;
class Map;
class MainMenuScene;
class Player;
#include "YouWinScene.h"
#include "Map.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Health.h"
#include "MainMenuScene.h"
#include <iostream>
#include <fstream>
#include "YouLoseScene.h"
using std::ofstream;

Map* map2;

Player* player2;

EnemyManager* enemyManager2;

BulletManager* bulletManager2;

Health* health2;

Level2Scene::Level2Scene(SDL_Renderer* renderer, Game* game)
{
	this->renderer = renderer;
	this->game = game;
}

void Level2Scene::init()
{
	int lvl = 2;
	map2 = new Map(renderer);

	player2 = new Player("assets/plantPlayer.png", renderer);
	player2->setMap(map2);
	player2->init(32, 32);

	std::cout << "Player initializat\n";
	health2 = new Health("assets/health.png", renderer);
	health2->setPlayer(player2);
	health2->init(0, 0);

	bulletManager2 = new BulletManager("assets/bullet.png", renderer);
	bulletManager2->setMap(map2);
	std::cout << "Bullet manager initializat\n";
	player2->setBulletManager(bulletManager2);

	enemyManager2 = new EnemyManager("assets/zombie.png", renderer);
	enemyManager2->setMap(map2);
	enemyManager2->setBulletManager(bulletManager2);
	enemyManager2->init(lvl, player2);

	std::cout << "Enemy manager initializat\n";
}

void Level2Scene::update()
{
	if (player2->isAlive())
		player2->update();
	else
	{
		player2->setTex("assets/deadPlayer.png");
		ofstream fileLevel("assets/Levels.txt");
		fileLevel << 2;
		Scene* scene = new YouLoseScene(renderer, game);
		scene->init();
		game->setScene(scene);
		fileLevel.close();
	}
	std::cout << "Player update\n";
	health2->update();
	if (enemyManager2->getNumberEnemies())
		enemyManager2->update();
	else
	{
		//lucru cu fisiere2
		if (player2->isAlive())
		{
			ofstream fileLevel("assets/Levels.txt");
			fileLevel << 2;
			Scene* scene = new YouWinScene(renderer, game);
			scene->init();
			game->setScene(scene);
			fileLevel.close();
		}
	}
	bulletManager2->update();
	std::cout << "Bullet manager update\n";
}

void Level2Scene::draw()
{
	SDL_RenderClear(renderer);
	// this is where we would add stuff to render
	map2->DrawMap();
	player2->draw();
	health2->draw();
	if (enemyManager2->getNumberEnemies())
		enemyManager2->draw();
	bulletManager2->draw();

	SDL_RenderPresent(renderer);
}

void Level2Scene::handleEvents(SDL_Event& event)
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
		player2->handleEvent(event);
		break;
	}
}       