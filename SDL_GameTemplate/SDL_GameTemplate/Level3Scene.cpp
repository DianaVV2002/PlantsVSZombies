class Enemy;
#include "Level3Scene.h"
#include "Map.h"
class Map;
class Player;
class EnemyManager;
class MainMenuScene;
#include"YouWinScene.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Health.h"
#include "MainMenuScene.h"
#include <iostream>
#include "FinalEnemy.h"
#include <fstream>
#include "YouLoseScene.h"
#include<iostream>
using std::ofstream;

Map* map3;

Player* player3;

EnemyManager* enemyManager3;

BulletManager* bulletManager3;

Health* health3;

FinalEnemy* finalEnemy;


Level3Scene::Level3Scene(SDL_Renderer* renderer, Game* game)
{
	this->renderer = renderer;
	this->game = game;
}

void Level3Scene::init()
{
	int lvl = 3;
	map3 = new Map(renderer);

	player3 = new Player("assets/plantPlayer.png", renderer);
	player3->setMap(map3);
	player3->init(32, 32);

	std::cout << "Player initializat\n";
	health3 = new Health("assets/health.png", renderer);
	health3->setPlayer(player3);
	health3->init(0, 0);

	bulletManager3 = new BulletManager("assets/bullet.png", renderer);
	bulletManager3->setMap(map3);
	player3->setBulletManager(bulletManager3);

	enemyManager3 = new EnemyManager("assets/zombie.png", renderer);
	enemyManager3->setMap(map3);
	enemyManager3->setBulletManager(bulletManager3);
	enemyManager3->init(lvl, player3);
	finalEnemy = new FinalEnemy("assets/finalZombie.png", renderer);
	finalEnemy->init(352, 352, player3, map3, bulletManager3);
	
}

void Level3Scene::update()
{
	if (player3->isAlive())
		player3->update();
	else
	{
		player3->setTex("assets/deadPlayer.png");
		ofstream fileLevel("assets/Levels.txt");
		fileLevel << 3;
		Scene* scene = new YouLoseScene(renderer, game);
		scene->init();
		game->setScene(scene);
		fileLevel.close();
	}
	health3->update();
	if (enemyManager3->getNumberEnemies())
		enemyManager3->update();
	else
	{
		if (player3->isAlive()&&!finalEnemy->isAlive())
		{
			ofstream fileLevel("assets/Levels.txt");
			fileLevel << 3;
			Scene* scene = new YouWinScene(renderer, game);
			scene->init();
			game->setScene(scene);
			fileLevel.close();
		}
	}
	bulletManager3->update();
	if(finalEnemy->isAlive())
		finalEnemy->update();
}

void Level3Scene::draw()
{
	SDL_RenderClear(renderer);
	// this is where we would add stuff to render
	map3->DrawMap();
	player3->draw();
	health3->draw();
	if(enemyManager3->getNumberEnemies())
	enemyManager3->draw();
	bulletManager3->draw();
	if (finalEnemy->isAlive())
		finalEnemy->draw();

	SDL_RenderPresent(renderer);
}

void Level3Scene::handleEvents(SDL_Event& event)
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
		player3->handleEvent(event);
		break;
	}
}