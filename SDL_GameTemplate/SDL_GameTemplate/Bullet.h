#pragma once
class EnemyManager;
class Enemy;
#include "Component.h"
#include "TextureManager.h"
#include "Map.h"

class Bullet :public Component
{
	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	SDL_Rect srcRect{}, destRect{};
	KEY_p direction;
	int speed;
	EnemyManager* enemyManager;
	Map* map;
public:
	 Bullet() = default;
	 Bullet(const char* path, SDL_Renderer * renderer);
	 void setTex(const char* path);
	 void init(int x, int y) override;
	 void setDirection(KEY_p dir);
	 void update() override;
	 void draw() override;
	 bool checkCollision(const SDL_Rect& r) override;
	 bool wallCollision();
	 void setEnemies(EnemyManager* enemyManager);
	 void setMap(Map* map);
};