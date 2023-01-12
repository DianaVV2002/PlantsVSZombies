#pragma once
class Map;
#include "Component.h"
#include "SDL.h"
#include "Player.h"

class Enemy : public Component
{
protected:

	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	SDL_Rect srcRect{}, destRect{}, hitbox{};
	KEY_p direction;
	int xspeed, yspeed;
	Player* target;
	Map* map;
public:
	Enemy() = default;
	Enemy(const char* path, SDL_Renderer* renderer);
	SDL_Rect getHitbox();
	void setTex(const char* path);

	void init(int x, int y) override;

	void update() override;

	void draw() override;

	bool checkCollision(const SDL_Rect& obj) ;

	void setTarget(Player* target);

	void followTarget();

	bool isWallBetween(int playerRow, int playerCol, int enemyRow, int enemyCol);
	
	bool playerCollision();

	SDL_Rect getEnemyPos();

	~Enemy();

	void setMap(Map* map);
};
