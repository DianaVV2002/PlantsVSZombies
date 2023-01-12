class Enemy;
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "TextureManager.h"

using namespace std;

Player::Player(const char* path, SDL_Renderer* renderer): renderer(renderer)
{
   setTex(path);
}

void Player::setTex(const char* path)
{
   texture = TextureManager::LoadTexture(path, renderer);
}

void Player::init(int x, int y)
{
   srcRect.x = srcRect.y = 0;
   srcRect.w = srcRect.h = 32;

   destRect.x = x;
   destRect.y = y;
   destRect.w = destRect.h = 32;
   xspeed = yspeed = 2;
   direction = DEFAULT;
   health = 3;
   lastDirection = RIGHT;

   timeSinceLastBullet = 61; // pentru a putea da glontul initial
}

void Player::update()
{
	timeSinceLastDirectionChange++;
	if (timeSinceLastDirectionChange > directionTimeout)
	{
		lastDirection = RIGHT;
		timeSinceLastDirectionChange = 0;
	}
	else
		if (direction != DEFAULT)
			lastDirection = direction;
	
	timeSinceLastBullet++;


	// y creste in jos
	int** map = this -> map -> GetMap();
	int lin = this -> map -> GetLin();
	int col = this -> map -> GetCol();

	int oldX = destRect.x;
	int oldY = destRect.y;
	
	switch (direction)
	{
	case UP:
		destRect.y -= yspeed;
		break;
	case DOWN:
		destRect.y += yspeed;
		break;
	case RIGHT:
		destRect.x += xspeed;
		break;
	case LEFT:
		destRect.x -= xspeed;
		break;
	default:
		direction = DEFAULT;
		break;  
    }
	
	/*cout << destRect.x << " " << destRect.y << " " << destRect.x + destRect.w << " " << destRect.y + destRect.h << "\n\n";*/
	bool isCollision = false;
	for(int row = 0; row < lin && isCollision == false; row++)
		for (int column = 0; column < col && isCollision == false; column++)
			if(map[row][column] == 1|| map[row][column] == 2)
			{
				SDL_Rect r = convertTileToRect(column * 32, row * 32, 32,32);
				 //cout << r.x << " " << r.y << " " << r.w << " " << r.h << '\n';
				isCollision = checkCollision(r);
			}

	if (isCollision == true)
	{
		//cout << "COLIZIUNE\n\n\n";
		destRect.x = oldX;
		destRect.y = oldY;
	}


	// De adaugat coliziune cu vectorul de inamici. Daca atingi un inamic se reseteaza x si y playerului la pozitia de start(32,32)
	
}


void Player::draw()
{
   TextureManager::Draw(texture, srcRect, destRect, renderer);
}

void Player::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		default:
			direction = DEFAULT;
			break;

		case SDLK_UP:
			direction = UP;
			break;

		case  SDLK_DOWN:
			direction = DOWN;
			break;

		case SDLK_RIGHT:
			direction = RIGHT;
			break;
			
		case SDLK_LEFT:
			direction = LEFT;
			break;
		case SDLK_SPACE:
			//std::cout << "Dau bullet\n";
			if (timeSinceLastBullet > bulletCooldown) // daca a trecut timpul de cooldown dau un nou glont si resetez timpul de cooldown la 0
			{
				bulletManager->addBullet(destRect.x, destRect.y, lastDirection);
				timeSinceLastBullet = 0;
			}
			break;
		}
	}

	if (event.type == SDL_KEYUP)
	{
		direction = DEFAULT;
	}

	
}

bool Player::checkCollision(const SDL_Rect& obj)
{
	SDL_Rect player = destRect;
	int a = 6; // indice de permisivitate ca sa trecem mai usor prin locuri stramte
	SDL_Rect permissiveObject{ obj.x + a, obj.y + a, obj.w - 2 * a, obj.h - 2 * a };
	
	if ((permissiveObject.x >= player.x + player.w) || (permissiveObject.x + permissiveObject.w <= player.x) || (permissiveObject.y >= player.y + player.h) || (permissiveObject.y+ permissiveObject.h <= player.y))
		return false;
	return true;
}
KEY_p Player::getPlayerDirection()
{
	return direction;
}
SDL_Rect Player::getPlayerPos()
{
	return destRect;
}
void Player::loseHealth()
{
	this->destRect.x = this->destRect.y = 32;
	health--;

}
bool Player::isAlive()
{
	return health != 0;
}
void Player::setBulletManager(BulletManager* bulletManager)
{
	this->bulletManager = bulletManager;
}
int Player::getHealth()
{
	return health;
}
void Player::setMap(Map* map)
{
	this->map = map;
}