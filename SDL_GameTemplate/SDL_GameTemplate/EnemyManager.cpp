class Enemy;
#include "EnemyManager.h"
#include <iostream>

EnemyManager::EnemyManager(const char* path, SDL_Renderer* renderer) : renderer(renderer)
{
	this->path = path;
}

void EnemyManager::init(int lvl, Player* player)
{
	target = player;
	if (lvl == 1)
	{
		this->n = 4;
		allEnemies = new Enemy*[n];
		for (int i = 0; i < n; i++)
		{
			allEnemies[i] = new Enemy(path,renderer);
			allEnemies[i]->setTarget(player);
			allEnemies[i]->setMap(map);
		}

		allEnemies[0]->init(160,160);
		allEnemies[1]->init(224, 224);
		allEnemies[2]->init(320, 320);
		allEnemies[3]->init(352, 352);
	}
	if (lvl == 2)
	{
		this->n = 7;
		allEnemies = new Enemy * [n];
		for (int i = 0; i < n; i++)
		{
			allEnemies[i] = new Enemy(path, renderer);
			allEnemies[i]->setTarget(player);
			allEnemies[i]->setMap(map);
		}

		allEnemies[0]->init(160, 160);
		allEnemies[1]->init(224, 224);
		allEnemies[2]->init(320, 320);
		allEnemies[3]->init(352, 160);
		allEnemies[4]->init(352, 352);
		allEnemies[5]->init(352, 352);
		allEnemies[6]->init(352, 352);
	}
	if (lvl == 3)
	{
		this->n = 7;
		allEnemies = new Enemy * [n];
		for (int i = 0; i < n; i++)
		{
			allEnemies[i] = new Enemy(path, renderer);
			allEnemies[i]->setTarget(player);
			allEnemies[i]->setMap(map);
		}

		allEnemies[0]->init(160, 160);
		allEnemies[1]->init(224, 224);
		allEnemies[2]->init(320, 320);
		allEnemies[3]->init(32, 287);
		allEnemies[4]->init(352, 352);
		allEnemies[5]->init(332, 352);
		allEnemies[6]->init(352, 352);

	
	}
}
void EnemyManager::clear()
{
	for (int i = 0; i < n; i++)
		delete allEnemies[i];
	delete[] allEnemies;

}

void swap(Enemy*& e1, Enemy*& e2)
{
	Enemy* aux;
	aux = e1;
	e1 = e2;
	e2 = aux;
}

void EnemyManager::update()
{
	
	for (int i = 0; i < n; i++)
		if (allEnemies[i]->playerCollision())
		{
				target->loseHealth();
				deleteEnemy(i);
		}
			else
			{
				bool enemyDead = false;
				for (int j = 0; j < bulletManager->getNumberBullets(); j++)
				{
					if (this->bulletCollision(bulletManager->getAllBullets()[j], allEnemies[i]))
					{
						deleteEnemy(i);
						bulletManager->deleteBullet(j);
						enemyDead = true;
					}
				}

				if (enemyDead == false)
					allEnemies[i]->update();
		
			}
	
	
}

bool EnemyManager::bulletCollision(Bullet* bullet, Enemy* enemy)
{
	return bullet->checkCollision(enemy->getEnemyPos());
}

void EnemyManager::draw()
{
	for (int i = 0; i < n; i++)
		allEnemies[i]->draw();
}
int EnemyManager::getNumberEnemies()
{
	return n;
}
Enemy** EnemyManager::getAllEnemies()
{
	return allEnemies;
}

void EnemyManager::deleteEnemy(int index)
{
	swap(allEnemies[index], allEnemies[n - 1]);
	delete allEnemies[n - 1];
	n--;
}

void EnemyManager::setBulletManager(BulletManager* bulletManager)
{
	this->bulletManager = bulletManager;
}

void EnemyManager::setMap(Map* map)
{
	this->map = map;
}