#pragma once
#include <iostream>

#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Nextable.h"
#include "DrawRaysOnMiniMap.h"

class Main3dDraw : public sf::Drawable, public Nextable
{
private:
	const int rayLength = 100;
	const int drawableRayLength = 100;
	const int raysQuantity = 300;

	std::vector<std::shared_ptr<sf::Drawable>> drawables;

	std::shared_ptr<std::vector<std::vector<int>>> map;
	std::shared_ptr<std::vector<sf::Vector2f>> rays;
	std::vector<int> whatBlockRayIntersect;
	std::vector<float> angles;
	
	std::vector<std::shared_ptr<sf::RectangleShape>> verticalRectangles;

	std::shared_ptr<sf::Texture> wallTexture;

	std::vector<std::shared_ptr<sf::Texture>> wallTextures;

	std::function<sf::Vector2f()> getPlayerPosition;
	std::function<float()> getPlayerAngle;
	std::function<sf::Vector2f()> getPlayerPixelPosition;

	static float length(sf::Vector2f vector);

	sf::Vector2f setIntersectionPosistion(
		int rayNumber, sf::Vector2f interSectionPosition, int blockNumber);

	void checkIntersectionRightDown(sf::Vector2f cubePosition,
		float k, float b, float pointY1, float pointY2, int i, int blockNumber);
	void checkIntersectionRightUp(sf::Vector2f cubePosition,
		float k, float b, float pointY1, float pointY2, int i, int blockNumber);
	void checkIntersectionLeftDown(sf::Vector2f cubePosition,
		float k, float b, float pointY1, float pointY2, int i, int blockNumber);
	void checkIntersectionLeftUp(sf::Vector2f cubePosition,
		float k, float b, float pointY1, float pointY2, int i, int blockNumber);

	void checkIntersection(sf::Vector2f cubePosition, int blockNumber);

	void generateVerticalRectabgles();

public:
	Main3dDraw(
		std::function<sf::Vector2f()> _getPlayerPosition,
		std::function<float()> _getPlayerAngle,
		std::function<sf::Vector2f()> _getPlayerPixelPosition,
		std::vector<std::vector<int>>& _map);

	void next() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

