#pragma once
#include <vector>
#include <iostream>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "PositionHavier.h"

class Enemy : public PositionHavier
{
public:
	Enemy(sf::Vector2f position);

	sf::Vector2f getPosition();

};

