#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Nextable.h"

#include "iostream"
#include <functional>

class MiniMap : public Nextable, public sf::Drawable
{
	std::vector<std::shared_ptr<sf::Drawable>> drawables;

	std::shared_ptr<sf::RectangleShape> blockShape;

	std::shared_ptr<sf::CircleShape> playerShape;

	std::shared_ptr<std::vector<std::vector<int>>> map;

	std::shared_ptr<sf::RectangleShape> borderShape;

	std::function<sf::Vector2f()> getPlayerPixelPosition;
	std::function<float()> getPlayerAngle;

public:

	MiniMap(
		std::function<sf::Vector2f()> _getPlayerPosition,
		std::function<float()> _getPlayerAngle,
		std::vector<std::vector<int>>& _map);

	void next() override;


	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

