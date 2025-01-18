#pragma once
#include <SFML/System.hpp>

class PositionHavier
{
protected:
	sf::Vector2f position;
public:
	float distanceTo(sf::Vector2f);
};

