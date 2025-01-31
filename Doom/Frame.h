#pragma once
#include <vector>
#include <iostream>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Nextable.h"

#include "Player.h"
#include "Enemy.h"
#include "MiniMap.h"

#include "Main3dDraw.h"

#include "GameCycle.h"

class Frame : public Nextable, public sf::Drawable
{
private:
	std::shared_ptr<Player> player;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::shared_ptr<MiniMap> miniMap;
	std::shared_ptr<Main3dDraw> main3dDraw;

	std::vector<std::shared_ptr<sf::Drawable>> drawables;
	std::vector<std::shared_ptr<Nextable>> nextables;

	static float distance(sf::Vector2f, sf::Vector2f);
	static float square(sf::Vector2f, sf::Vector2f, sf::Vector2f);

	static bool checkPointInQuadrilateral(sf::Vector2f point,
		sf::Vector2f pointQuadrilateral1,
		sf::Vector2f pointQuadrilateral2,
		sf::Vector2f pointQuadrilateral3,
		sf::Vector2f pointQuadrilateral4);

	static sf::Vector2f findIntersection(
		sf::Vector2f position11,
		sf::Vector2f position12,
		sf::Vector2f position21,
		sf::Vector2f position22);

	static sf::Vector2f checkInterseption(
		sf::Vector2f position11,
		sf::Vector2f position12,
		sf::Vector2f position21,
		sf::Vector2f position22);

public:
	Frame();

	void next();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

