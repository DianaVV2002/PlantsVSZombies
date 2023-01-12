#pragma once
class BulletManager;
class Enemy;
#include "Component.h"
#include "BulletManager.h"

class Player : public Component
{
	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	SDL_Rect srcRect{}, destRect{};
	KEY_p direction;
	int xspeed, yspeed;
	int health;
	BulletManager* bulletManager;
	int bulletCooldown = 30; // fps e 60, deci 1 bullet pe secunda
	int timeSinceLastBullet;
	int directionTimeout = 15; // daca nu s-a schimbat directia in ultimele 15 frame-uri(0.25 secunde), atunci directia implicita va fi dreapta 
	int timeSinceLastDirectionChange;
	KEY_p lastDirection;
	Map* map;
public:
   Player() = default;
   Player(const char* path, SDL_Renderer* renderer);

	void setTex(const char* path);

	void init(int x, int y) override;

	void update() override;//aici se face miscarea

	void draw() override;//deseneaza noua pozitie

	void handleEvent(SDL_Event& event);//seteaza directia

	bool checkCollision(const SDL_Rect& obj);

    KEY_p getPlayerDirection();

	SDL_Rect getPlayerPos();

	void loseHealth();

	bool isAlive();

	void setBulletManager(BulletManager* bulletManager);

	int getHealth();

	void setMap(Map* map);
};
