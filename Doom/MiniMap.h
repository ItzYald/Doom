#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Nextable.h"

#include "iostream"
#include <functional>

class MiniMap : public Nextable, public sf::Drawable
{
	std::shared_ptr<sf::CircleShape> playerShape;

	std::shared_ptr<sf::RectangleShape> borderShape;

	std::vector<std::shared_ptr<sf::Drawable>> drawables;

	std::function<sf::Vector2f()> getPlayerPosition;
	std::function<float()> getPlayerAngle;

public:

	MiniMap(
		std::function<sf::Vector2f()> _getPlayerPosition,
		std::function<float()> _getPlayerAngle);

	void next() override;


	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

