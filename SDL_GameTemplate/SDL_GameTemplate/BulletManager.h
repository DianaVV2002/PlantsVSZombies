#pragma once
class Bullet;
class Enemy;
#include "Bullet.h"
#include "TextureManager.h"

class BulletManager
{
	const char* path;
	SDL_Renderer* renderer{};
	Bullet** allBullets;
	Map* map;
	int n;
public:
	BulletManager() = default;
	BulletManager(const char* path, SDL_Renderer * renderer);
	void addBullet(int x, int y, KEY_p direction);
	void update();
	void draw();
	int getNumberBullets();
	Bullet** getAllBullets();
	void deleteBullet(int index);
	~BulletManager();
	void setMap(Map* map);
};