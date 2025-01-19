#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Nextable.h"
#include "PositionHavier.h"

class Player : public sf::Drawable, public Nextable, public PositionHavier
{
	sf::CircleShape shape;

	float angle;

	const float speed = 2;

public:
	Player();

	sf::Vector2f getPosition();

	void move();

	void next() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

