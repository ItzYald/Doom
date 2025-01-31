#include "Player.h"

constexpr auto PI = 3.1415926535;

Player::Player()
{
	font = sf::Font();
	font.loadFromFile("arial.ttf");

	shape = sf::CircleShape(6);

	shape.setPosition(sf::Vector2f(100, 100));
	shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));

	position = sf::Vector2f(5, 5);

	angle = 0;
}

sf::Vector2f Player::getPixelPosition()
{
	return position * 20.f + sf::Vector2f(0, 520);
}

sf::Vector2f Player::getPosition()
{
	return position;
}

float Player::getAngle()
{
	return angle;
}

void Player::borderControl()
{
	if (position.x > Constants::quantityCells) position.x = Constants::quantityCells;
	if (position.y > Constants::quantityCells) position.y = Constants::quantityCells;
	if (position.x < 0) position.x = 0;
	if (position.y < 0) position.y = 0;
	shape.setPosition(position);
}

bool Player::moveDiagonal()
{
	bool result = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		position += sf::Vector2f(speed * sin(angle + PI / 4), speed * cos(angle + PI / 4));
		result = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		position += sf::Vector2f(speed * sin(angle - PI / 4), speed * cos(angle - PI / 4));
		result = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		position -= sf::Vector2f(speed * sin(angle - PI / 4), speed * cos(angle - PI / 4));
		result = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		position -= sf::Vector2f(speed * sin(angle + PI / 4), speed * cos(angle + PI / 4));
		result = true;
	}
	return result;
}

void Player::moveStraight()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		position += sf::Vector2f(speed * sin(angle), speed * cos(angle));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		position -= sf::Vector2f(speed * sin(angle), speed * cos(angle));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		position += sf::Vector2f(speed * sin(angle + PI / 2), speed * cos(angle + PI / 2));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		position += sf::Vector2f(speed * sin(angle - PI / 2), speed * cos(angle - PI / 2));
	}
}

void Player::move()
{
	if (!moveDiagonal())
		moveStraight();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		angle += 0.05f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		angle -= 0.05f;
	}
}

void Player::next()
{
	move();
	borderControl();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Text text = sf::Text("x: " + std::to_string(position.x) + " y:" + std::to_string(position.y), font);
	target.draw(text, states);
}


