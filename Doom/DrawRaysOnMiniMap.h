#pragma once
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


class DrawRaysOnMiniMap : public sf::Drawable
{
private:
	std::function<sf::Vector2f()> getPlayerPosition;
	std::function<sf::Vector2f()> getPlayerPixelPosition;
	int raysQuantity;
	std::shared_ptr<std::vector<sf::Vector2f>> rays;

public:
	DrawRaysOnMiniMap(std::function<sf::Vector2f()> _getPlayerPosition,
		std::function<sf::Vector2f()> _getPlayerPixelPosition, int _raysQantity,
		std::shared_ptr<std::vector<sf::Vector2f>>& _rays);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

