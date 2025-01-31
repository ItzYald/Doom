#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position)
{
	this->position = position;
}

sf::Vector2f Enemy::getPosition()
{
	return position;
}
