#pragma once
#include <iostream>

#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Nextable.h"

class Main3dDraw : public sf::Drawable, public Nextable
{
private:
	const int rayLength = 100;
	const int drawableRayLength = 100;
	const int raysQuantity = 100;

	std::vector<sf::Vector2f> intersectionsPositions;

	std::vector<std::shared_ptr<sf::Drawable>> drawables;

	std::shared_ptr<std::vector<std::vector<int>>> map;
	std::vector<sf::Vector2f> rays;

	std::function<sf::Vector2f()> getPlayerPosition;
	std::function<float()> getPlayerAngle;
	std::function<sf::Vector2f()> getPlayerPixelPosition;

	float length(sf::Vector2f vector);

	sf::Vector2f setIntersectionPosistion(int rayNumber, sf::Vector2f interSectionPosition);

	sf::Vector2f checkIntersection(sf::Vector2f cubePosition);

public:
	Main3dDraw(
		std::function<sf::Vector2f()> _getPlayerPosition,
		std::function<float()> _getPlayerAngle,
		std::function<sf::Vector2f()> _getPlayerPixelPosition,
		std::vector<std::vector<int>>& _map);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void next() override;

};

