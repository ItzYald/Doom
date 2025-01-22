#include "Main3dDraw.h"

#define PI 3.1415926535

Main3dDraw::Main3dDraw(
	std::function<sf::Vector2f()> _getPlayerPosition,
	std::function<float()> _getPlayerAngle,
	std::function<sf::Vector2f()> _getPlayerPixelPosition,
	std::vector<std::vector<int>>& _map)
{
	drawables = std::vector<std::shared_ptr<sf::Drawable>>();

	rays = std::vector<sf::Vector2f>();

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

sf::Vector2f Main3dDraw::setIntersectionPosistion(int rayNumber, sf::Vector2f interSectionPosition)
{
	float len1 = length(rays[rayNumber] - getPlayerPosition());
	float len2 = length(interSectionPosition - getPlayerPosition());
	if (len1 > len2)
		return interSectionPosition;
	else
		return rays[rayNumber];
}

sf::Vector2f Main3dDraw::checkIntersection(sf::Vector2f cubePosition)
{
	for (size_t i = 0; i < rays.size(); i++)
	{
		float k = (rays[i].y - getPlayerPosition().y) / (rays[i].x - getPlayerPosition().x);
		float b = -getPlayerPosition().x * k + getPlayerPosition().y;

		float pointY1 = cubePosition.x * k + b;
		float pointY2 = (cubePosition.x + 1) * k + b;
		
		if (k > 0)
		{
			if (rays[i].x > getPlayerPosition().x)
			{
				if (pointY2 < cubePosition.y ||
					getPlayerPosition().y > cubePosition.y + 1 || 
					getPlayerPosition().x > cubePosition.x + 1) continue;
				if (pointY1 < cubePosition.y && pointY2 > cubePosition.y)
				{
					rays[i] = setIntersectionPosistion(i,
						sf::Vector2f((cubePosition.y - b) / k, cubePosition.y));
				}
				if (pointY1 < cubePosition.y + 1 && pointY1 > cubePosition.y)
				{
					rays[i] = setIntersectionPosistion(i,
						sf::Vector2f(cubePosition.x, pointY1));
				}
			}
			else
			{
				if (pointY1 > cubePosition.y + 1 || 
					getPlayerPosition().y < cubePosition.y || 
					pointY2 < cubePosition.y ||
					getPlayerPosition().x < cubePosition.x) continue;
				if (pointY2 >= cubePosition.y + 1 && pointY1 < cubePosition.y + 1)
				{
					rays[i] = setIntersectionPosistion(i,
						sf::Vector2f((cubePosition.y + 1 - b) / k, cubePosition.y + 1));
				}
				if (pointY2 < cubePosition.y + 1 && pointY2 > cubePosition.y)
				{
					rays[i] = setIntersectionPosistion(i,
						sf::Vector2f(cubePosition.x + 1, pointY2));
				}
			}
		}
		else
		{
			if (rays[i].x > getPlayerPosition().x)
			{
				if (pointY1 < cubePosition.y ||
					getPlayerPosition().y < cubePosition.y ||
					pointY2 > cubePosition.y + 1 ||
					getPlayerPosition().x > cubePosition.x + 1) continue;

				if (pointY1 >= cubePosition.y + 1 && pointY2 < cubePosition.y + 1)
				{
					rays[i] = setIntersectionPosistion(i,
						sf::Vector2f((cubePosition.y + 1 - b) / k, cubePosition.y + 1));
				}
				if (pointY1 > cubePosition.y && pointY1 < cubePosition.y + 1)
				{
					rays[i] = setIntersectionPosistion(i,
						sf::Vector2f(cubePosition.x, pointY1));
				}
			}
			else
			{
				if (pointY2 > cubePosition.y + 1 ||
					getPlayerPosition().y > cubePosition.y + 1 ||
					getPlayerPosition().x < cubePosition.x) continue;
				if (pointY2 < cubePosition.y && pointY1 > cubePosition.y)
				{
					rays[i] = setIntersectionPosistion(i,
						sf::Vector2f((cubePosition.y - b) / k, cubePosition.y));
				}
				if (pointY2 < cubePosition.y + 1 && pointY2 > cubePosition.y)
				{
					rays[i] = setIntersectionPosistion(i,
						sf::Vector2f(cubePosition.x + 1, pointY2));
				}
			}
		}

	}


	return sf::Vector2f();
}

void Main3dDraw::next()
{
	rays.clear();
	for (int i = raysQuantity * -1; i < raysQuantity; i++)
	{
		float angle = getPlayerAngle() + PI  / raysQuantity / 2 * (i);
		rays.push_back(getPlayerPosition() + sf::Vector2f(rayLength * sin(angle), rayLength * cos(angle)));
	}

	for (size_t i = 0; i < (*map).size(); i++)
	{
		for (int j = 0; j < (*map).size(); j++)
		{
			if ((*map)[i][j] == 1)
			{
				checkIntersection(sf::Vector2f(j, i));
			}
		}
	}
}

void Main3dDraw::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Vertex line[2];
	line[0] = sf::Vertex(getPlayerPixelPosition());

	std::vector<sf::Vector2f> drawableRays = std::vector<sf::Vector2f>();

	sf::CircleShape shape = sf::CircleShape(5);
	shape.setOrigin(shape.getRadius(), shape.getRadius());

	for (size_t i = 0; i < intersectionsPositions.size(); i++)
	{
		shape.setPosition(intersectionsPositions[i] * 20.f + sf::Vector2f(0, 520));
		target.draw(shape, states);
	}

	for (int i = raysQuantity * -1; i < raysQuantity; i++)
	{
		drawableRays.push_back((rays[i + raysQuantity] - getPlayerPosition()) * 20.f + line[0].position);

		line[1] = sf::Vertex(drawableRays[i + raysQuantity]);

		target.draw(line, 2, sf::Lines);
	}
}

