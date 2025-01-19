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
	shape.setPosition(position);
}

void Player::next()
{
	move();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Vertex line[2]{
		sf::Vertex(position),
		sf::Vertex(position + sf::Vector2f(30 * sin(angle), 30 * cos(angle)))
	};

	target.draw(line, 2, sf::Lines);

	target.draw(shape, states);
}


