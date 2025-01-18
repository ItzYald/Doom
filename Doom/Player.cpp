#include "Player.h"

Player::Player()
{
	shape = sf::CircleShape(6);

	shape.setPosition(sf::Vector2f(100, 100));

	position = sf::Vector2f(position);

}

void Player::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		position.y -= 1;
	}
	shape.setPosition(position);
}

void Player::next()
{
	move();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}


