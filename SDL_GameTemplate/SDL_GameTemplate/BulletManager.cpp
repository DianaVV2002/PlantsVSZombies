class Enemy;
#include "BulletManager.h"
#include <iostream>

BulletManager::BulletManager(const char* path, SDL_Renderer* renderer): renderer(renderer)
{
	this->path = path;
	this->n = 0;
	allBullets = new Bullet * [100];
}

void BulletManager::addBullet(int x, int y, KEY_p direction)
{
	Bullet* newBullet = new Bullet(path, renderer);
	newBullet->init(x, y);
	newBullet->setDirection(direction);
	newBullet->setMap(map);
    allBullets[n++] = newBullet;
	//std::cout << "S-a adaugat un bullet\n";
}

void BulletManager::update()
{
	//std::cout << "Numar bullet: " << n << '\n';
	for (int i = 0; i < n; i++)
	{
		//std::cout << "Bullet before update\n";
		
		if (allBullets[i]->wallCollision())
			deleteBullet(i);
		else
		{
			//std::cout << allBullets[i]->destRect.x << " " << allBullets[i]->destRect.y << '\n';
			allBullets[i]->update();
		}

		//std::cout << "Bullet update\n";
	}
}
void BulletManager::draw()
{
	for (int i = 0; i < n; i++)
		allBullets[i]->draw();
}
void swap(Bullet*& e1, Bullet*& e2)
{
	Bullet* aux;
	aux = e1;
	e1 = e2;
	e2 = aux;
}
int BulletManager::getNumberBullets()
{
	return n;
}
Bullet** BulletManager::getAllBullets()
{
	return allBullets;
}
void BulletManager::deleteBullet(int index)
{
	if (index >= n)
		std::cout << "NU EXISTA BULLETUL ACELA\n";
	else
	{
		swap(allBullets[index], allBullets[n - 1]);
		delete allBullets[n - 1];
		n--;
	}
}
BulletManager::~BulletManager()
{

}

void BulletManager::setMap(Map* map)
{
	this->map = map;
}