class Enemy;
#include "EnemyManager.h"
#include "Bullet.h"
#include "Map.h"

Bullet::Bullet(const char* path, SDL_Renderer* renderer) : renderer(renderer)
{
	setTex(path);
}
void Bullet::setTex(const char* path)
{
	texture = TextureManager::LoadTexture(path, renderer);
}
void Bullet::init(int x, int y)
{
	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 32;
	destRect.w = destRect.h = 32;
	destRect.x = x;
	destRect.y = y;
	speed = 4;

}
void Bullet::setDirection(KEY_p dir)
{
	direction = dir;
}
void Bullet::update() {
	//std::cout << "Sunt bullet si ma misc\n";
	std::cout << direction << '\n';

	switch (direction)
	{
	case UP:
		destRect.y -= speed;
		break;
	case DOWN:
		destRect.y += speed;
		break;
	case RIGHT:
		destRect.x += speed;
		break;
	case LEFT:
		destRect.x -= speed;
		break;
	case DEFAULT:
		break;
	}

}

void Bullet::draw() {
	//std::cout << "Sunt bullet si ma desenez\n\n";
	TextureManager::Draw(texture, srcRect, destRect, renderer);
}
bool Bullet::checkCollision(const SDL_Rect& obj)
{
	SDL_Rect enemy = destRect;
	int a = 10; // indice de permisivitate ca sa trecem mai usor prin locuri stramte
	SDL_Rect permissiveObject{ obj.x + a, obj.y + a, obj.w - 2 * a, obj.h - 2 * a };

	if ((permissiveObject.x >= enemy.x + enemy.w) || (permissiveObject.x + permissiveObject.w <= enemy.x) || (permissiveObject.y >= enemy.y + enemy.h) || (permissiveObject.y + permissiveObject.h <= enemy.y))
		return false;
	return true;
}
bool Bullet::wallCollision()
{
	int** map = this -> map ->GetMap();
	int lin = this -> map -> GetLin();
	int col = this -> map -> GetCol();
	bool isCollision = false;
	for (int row = 0; row < lin && isCollision == false; row++)
		for (int column = 0; column < col && isCollision == false; column++)
			if (map[row][column] == 1)
			{
				SDL_Rect r = convertTileToRect(column * 32, row * 32, 32, 32);
				//cout << r.x << " " << r.y << " " << r.w << " " << r.h << '\n';
				isCollision = checkCollision(r);
			}
	return isCollision;
}

void Bullet::setEnemies(EnemyManager* enemyManager)
{
	this->enemyManager = enemyManager;
}

void Bullet::setMap(Map *map)
{
	this->map = map;
}
