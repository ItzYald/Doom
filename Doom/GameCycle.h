#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Frame.h"

class GameCycle
{
private:

public:

	static inline std::shared_ptr<sf::RenderWindow> window;

	GameCycle();
};

