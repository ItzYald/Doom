#include "DrawRaysOnMiniMap.h"

DrawRaysOnMiniMap::DrawRaysOnMiniMap(
	std::function<sf::Vector2f()> _getPlayerPosition,
	std::function<sf::Vector2f()> _getPlayerPixelPosition, int _raysQantity,
	std::shared_ptr<std::vector<sf::Vector2f>>& _rays)
{
	getPlayerPosition = _getPlayerPosition;
	getPlayerPixelPosition = _getPlayerPixelPosition;
	raysQuantity = _raysQantity;

	rays = _rays;
}

void DrawRaysOnMiniMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if ((*rays).size() == 0) return;

	sf::Vertex line[2];
	line[0] = sf::Vertex(getPlayerPixelPosition());
	line[0].color = sf::Color::Red;
	line[1] = sf::Vertex(sf::Vector2f(0, 0), sf::Color::Red);

	std::vector<sf::Vector2f> drawableRays = std::vector<sf::Vector2f>();

	for (int i = raysQuantity * -1; i < raysQuantity; i++)
	{
		drawableRays.push_back(((*rays)[i + raysQuantity] - getPlayerPosition()) * 20.f + line[0].position);

		line[1].position = drawableRays[i + raysQuantity];

		target.draw(line, 2, sf::Lines);
	}
}
