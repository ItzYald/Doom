#include "Main3dDraw.h"

constexpr auto PI = 3.1415926535;

Main3dDraw::Main3dDraw(
	std::function<sf::Vector2f()> _getPlayerPosition,
	std::function<float()> _getPlayerAngle,
	std::function<sf::Vector2f()> _getPlayerPixelPosition,
	std::vector<std::vector<int>>& _map)
{
	drawables = std::vector<std::shared_ptr<sf::Drawable>>();

	rays = std::make_shared<std::vector<sf::Vector2f>>();
	angles = std::vector<float>();

	verticalRectangles = std::vector<std::shared_ptr<sf::RectangleShape>>();
	wallTexture = std::make_shared<sf::Texture>();
	wallTexture->loadFromFile("Images/wall1.png");

	for (size_t i = 0; i < raysQuantity * 2; i++)
	{
		verticalRectangles.push_back(std::make_shared<sf::RectangleShape>());
		verticalRectangles[i]->setSize(sf::Vector2f(1280 / (float)raysQuantity / 2.f, 0));
		verticalRectangles[i]->setOrigin(sf::Vector2f(verticalRectangles[i]->getSize().x / 2, 0));
		verticalRectangles[i]->setFillColor(sf::Color::White);
		verticalRectangles[i]->setPosition(sf::Vector2f(
			1280 - verticalRectangles[i]->getSize().x * i,
			720 / 2.f
		));
		verticalRectangles[i]->setTexture(wallTexture.get());
		drawables.push_back(verticalRectangles[i]);
	}

	drawables.push_back(std::make_shared<DrawRaysOnMiniMap>(
		_getPlayerPosition, _getPlayerPixelPosition,
		raysQuantity, rays
		));

	map = std::make_shared<std::vector<std::vector<int>>>(_map);

	getPlayerPosition = _getPlayerPosition;
	getPlayerAngle = _getPlayerAngle;
	getPlayerPixelPosition = _getPlayerPixelPosition;

	for (size_t i = 0; i < (*map).size(); i++)
	{
		for (int j = 0; j < (*map)[0].size(); j++)
		{
			std::cout << (*map)[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

float Main3dDraw::length(sf::Vector2f vector)
{
	return sqrtf(vector.x * vector.x + vector.y * vector.y);
}

void Main3dDraw::generateVerticalRectabgles()
{
	for (size_t i = 0; i < verticalRectangles.size(); i++)
	{
		if (length((*rays)[i] - getPlayerPosition()) + 1 >= rayLength)
		{
			verticalRectangles[i]->setSize(sf::Vector2f(
				verticalRectangles[i]->getSize().x, 0));
		}
		else
		{
			verticalRectangles[i]->setSize(sf::Vector2f(
				verticalRectangles[i]->getSize().x,
				600 / (length((*rays)[i] - getPlayerPosition())
					* cos(angles[i]))));

			if ((*rays)[i].x == (float)(int)(*rays)[i].x)
			{
				verticalRectangles[i]->setTextureRect(sf::IntRect(
					((*rays)[i].y - (int)(*rays)[i].y) * 1200, 0,
					10 / (length((*rays)[i] - getPlayerPosition()) * cos(angles[i])),
						1200));
			}
			else
			{
				verticalRectangles[i]->setTextureRect(sf::IntRect(
					((*rays)[i].x - (int)(*rays)[i].x) * 1200, 0,
					10 / (length((*rays)[i] - getPlayerPosition()) * cos(angles[i])),
					1200));
			}

		}
		
		verticalRectangles[i]->setOrigin(
			verticalRectangles[i]->getSize() / 2.f
		);

	}
}

sf::Vector2f Main3dDraw::setIntersectionPosistion(int rayNumber, sf::Vector2f interSectionPosition)
{
	float len1 = length((*rays)[rayNumber] - getPlayerPosition());
	float len2 = length(interSectionPosition - getPlayerPosition());
	if (len1 > len2)
		return interSectionPosition;
	else
		return (*rays)[rayNumber];
}

void Main3dDraw::checkIntersectionRightDown(sf::Vector2f cubePosition,
	float k, float b, float pointY1, float pointY2, int i)
{
	if (pointY2 < cubePosition.y ||
		getPlayerPosition().y > cubePosition.y + 1 ||
		getPlayerPosition().x > cubePosition.x + 1) return;
	if (pointY1 < cubePosition.y && pointY2 > cubePosition.y)
	{
		(*rays)[i] = setIntersectionPosistion(i,
			sf::Vector2f((cubePosition.y - b) / k, cubePosition.y));
	}
	else if (pointY1 < cubePosition.y + 1 && pointY1 > cubePosition.y)
	{
		(*rays)[i] = setIntersectionPosistion(i,
			sf::Vector2f(cubePosition.x, pointY1));
	}
}

void Main3dDraw::checkIntersectionRightUp(sf::Vector2f cubePosition,
	float k, float b, float pointY1, float pointY2, int i)
{
	if (pointY1 < cubePosition.y ||
		getPlayerPosition().y < cubePosition.y ||
		pointY2 > cubePosition.y + 1 ||
		getPlayerPosition().x > cubePosition.x + 1) return;
	if (pointY1 >= cubePosition.y + 1 && pointY2 < cubePosition.y + 1)
	{
		(*rays)[i] = setIntersectionPosistion(i,
			sf::Vector2f((cubePosition.y + 1 - b) / k, cubePosition.y + 1));
	}
	else if (pointY1 > cubePosition.y && pointY1 < cubePosition.y + 1)
	{
		(*rays)[i] = setIntersectionPosistion(i,
			sf::Vector2f(cubePosition.x, pointY1));
	}
}

void Main3dDraw::checkIntersectionLeftDown(sf::Vector2f cubePosition,
	float k, float b, float pointY1, float pointY2, int i)
{
	if (pointY2 > cubePosition.y + 1 ||
		getPlayerPosition().y > cubePosition.y + 1 ||
		getPlayerPosition().x < cubePosition.x) return;
	if (pointY2 < cubePosition.y && pointY1 > cubePosition.y)
	{
		(*rays)[i] = setIntersectionPosistion(i,
			sf::Vector2f((cubePosition.y - b) / k, cubePosition.y));
	}
	else if (pointY2 < cubePosition.y + 1 && pointY2 > cubePosition.y)
	{
		(*rays)[i] = setIntersectionPosistion(i,
			sf::Vector2f(cubePosition.x + 1, pointY2));
	}
}

void Main3dDraw::checkIntersectionLeftUp(sf::Vector2f cubePosition,
	float k, float b, float pointY1, float pointY2, int i)
{
	if (pointY1 > cubePosition.y + 1 ||
		getPlayerPosition().y < cubePosition.y ||
		pointY2 < cubePosition.y ||
		getPlayerPosition().x < cubePosition.x) return;
	if (pointY2 >= cubePosition.y + 1 && pointY1 < cubePosition.y + 1)
	{
		(*rays)[i] = setIntersectionPosistion(i,
			sf::Vector2f((cubePosition.y + 1 - b) / k, cubePosition.y + 1));
	}
	else if (pointY2 < cubePosition.y + 1 && pointY2 > cubePosition.y)
	{
		(*rays)[i] = setIntersectionPosistion(i,
			sf::Vector2f(cubePosition.x + 1, pointY2));
	}
}

void Main3dDraw::checkIntersection(sf::Vector2f cubePosition)
{
	for (size_t i = 0; i < (*rays).size(); i++)
	{
		float k = ((*rays)[i].y - getPlayerPosition().y) / ((*rays)[i].x - getPlayerPosition().x);
		float b = -getPlayerPosition().x * k + getPlayerPosition().y;

		float pointY1 = cubePosition.x * k + b;
		float pointY2 = (cubePosition.x + 1) * k + b;
		
		if (k > 0)
		{
			if ((*rays)[i].x > getPlayerPosition().x)
				checkIntersectionRightDown(cubePosition,
					k, b, pointY1, pointY2, i);
			else
				checkIntersectionLeftUp(cubePosition,
					k, b, pointY1, pointY2, i);
		}
		else
		{
			if ((*rays)[i].x > getPlayerPosition().x)
				checkIntersectionRightUp(cubePosition,
					k, b, pointY1, pointY2, i);
			else
				checkIntersectionLeftDown(cubePosition,
					k, b, pointY1, pointY2, i);
		}
	}
}

void Main3dDraw::next()
{
	(*rays).clear();
	angles.clear();
	for (int i = raysQuantity * -1; i < raysQuantity; i++)
	{
		float angle = getPlayerAngle() + PI / 2.f / raysQuantity / 2 * (i);
		angles.push_back(PI / 2 / raysQuantity / 2 * (i));
		(*rays).push_back(getPlayerPosition() + sf::Vector2f(rayLength * sin(angle), rayLength * cos(angle)));
	}

	for (size_t i = 0; i < (*map).size(); i++)
	{
		for (int j = 0; j < (*map).size(); j++)
		{
			if ((*map)[i][j] == 1)
				checkIntersection(sf::Vector2f(j, i));
		}
	}
	generateVerticalRectabgles();
}

void Main3dDraw::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto drawable : drawables)
	{
		target.draw(*drawable, states);
	}
}

