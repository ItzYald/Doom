#include "MiniMap.h"

//MiniMap::MiniMap(sf::Vector2f(*_getPlayerPosition)())
MiniMap::MiniMap(
	std::function<sf::Vector2f()> _getPlayerPosition,
	std::function<float()> _getPlayerAngle,
	std::vector<std::vector<int>>& _map)
{
	drawables = std::vector<std::shared_ptr<sf::Drawable>>();

	map = std::make_shared<std::vector<std::vector<int>>>(_map);

	blockShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(20, 20));
	blockShape->setFillColor(sf::Color::Transparent);
	blockShape->setOutlineColor(sf::Color::White);
	blockShape->setOutlineThickness(1);

	borderShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(200, 200));
	borderShape->setFillColor(sf::Color::Transparent);
	borderShape->setOutlineColor(sf::Color::White);
	borderShape->setOutlineThickness(3);
	borderShape->setPosition(sf::Vector2f(0, 520));
	drawables.push_back(borderShape);

	playerShape = std::make_shared<sf::CircleShape>(6);
	playerShape->setOrigin(playerShape->getRadius(), playerShape->getRadius());
	drawables.push_back(playerShape);

	getPlayerPosition = _getPlayerPosition;
	getPlayerAngle = _getPlayerAngle;
}

void MiniMap::next()
{
	playerShape->setPosition(getPlayerPosition() * 20.f + sf::Vector2f(0, 520));
}

void MiniMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (size_t i = 0; i < (*map).size(); i++)
	{
		for (size_t j = 0; j < (*map)[i].size(); j++)
		{
			if ((*map)[j][i] == 1)
			{
				blockShape->setPosition(borderShape->getPosition() + sf::Vector2f(20 * i, 20 * j));
				target.draw(*blockShape, states);
			}
		}
	}

	for (auto drawable : drawables)
	{
		target.draw(*drawable, states);
	}

	sf::Vertex line[2]{
		sf::Vertex(playerShape->getPosition()),
		sf::Vertex(playerShape->getPosition() +
			sf::Vector2f(30 * sin(getPlayerAngle()), 30 * cos(getPlayerAngle())))
	};
	target.draw(line, 2, sf::Lines);
}
