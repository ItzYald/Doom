#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Nextable.h"
#include "PositionHavier.h"
#include "Constants.h"

class Player : public sf::Drawable, public Nextable, public PositionHavier
{
	sf::Font font;

	sf::CircleShape shape;

	float angle;

	const float speed = 0.05f;

	void borderControl();

	bool moveDiagonal();

	void moveStraight();

	void move();

public:
	Player();

	sf::Vector2f getPixelPosition();
	sf::Vector2f getPosition();
	float getAngle();

	void next() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

