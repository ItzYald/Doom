#include "MiniMap.h"

//MiniMap::MiniMap(sf::Vector2f(*_getPlayerPosition)())
MiniMap::MiniMap(std::function<sf::Vector2f()> _getPlayerPosition)
{
	drawables = std::vector<std::shared_ptr<sf::Drawable>>();

	playerShape = std::make_shared<sf::CircleShape>(6);
	drawables.push_back(playerShape);

	getPlayerPosition = _getPlayerPosition;
}

void MiniMap::next()
{
	playerShape->setPosition(getPlayerPosition() / 10.f + sf::Vector2f(0, 200));
}

void MiniMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto drawable : drawables)
	{
		target.draw(*drawable, states);
	}
}
