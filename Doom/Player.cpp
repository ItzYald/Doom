#include "Player.h"

Player::Player()
{
	shape = sf::CircleShape(6);

	shape.setPosition(sf::Vector2f(100, 100));
	shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));

	position = sf::Vector2f(100, 100);

	angle = 0;
}

sf::Vector2f Player::getPosition()
{
	return position;
}

float Player::getAngle()
{
	return angle;
}

void Player::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		position += sf::Vector2f(speed * sin(angle), speed * cos(angle));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		position -= sf::Vector2f(speed * sin(angle), speed * cos(angle));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		angle += 0.1f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		angle -= 0.1f;
	}
	if (position.x > 20) position.x = 20;
	if (position.y > 20) position.y = 20;
	if (position.x < 0) position.x = 0;
	if (position.y < 0) position.y = 0;
	shape.setPosition(position);
}

void Player::next()
{
	move();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}


