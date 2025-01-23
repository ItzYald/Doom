#include "Frame.h"

Frame::Frame()
{
	drawables = std::vector<std::shared_ptr<sf::Drawable>>();
	nextables = std::vector<std::shared_ptr<Nextable>>();

	std::vector<std::vector<int>> map = std::vector<std::vector<int>>
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 0, 1, 1, 1},
		{1, 0, 0, 2, 2, 0, 0, 1, 1, 1},
		{1, 0, 0, 2, 2, 0, 0, 0, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	player = std::make_shared<Player>();
	nextables.push_back(player);
	drawables.push_back(player);

	miniMap = std::make_shared<MiniMap>(
		[&]() { return player->getPixelPosition(); },
		[&]() { return player->getAngle(); },
		map
	);
	nextables.push_back(miniMap);

	main3dDraw = std::make_shared<Main3dDraw>(
		[&]() { return player->getPosition(); },
		[&]() { return player->getAngle(); },
		[&]() { return player->getPixelPosition(); },
		map
	);
	nextables.push_back(main3dDraw);
	drawables.push_back(main3dDraw);
	drawables.push_back(miniMap);
}

float Frame::distance(sf::Vector2f position1, sf::Vector2f position2)
{
	float dX = position1.x - position2.x;
	float dY = position1.y - position2.y;

	return sqrtf(dX * dX + dY * dY);
}

float Frame::square(sf::Vector2f position1, sf::Vector2f position2, sf::Vector2f position3)
{
	float distance1 = distance(position1, position2);
	float distance2 = distance(position1, position3);
	float distance3 = distance(position2, position3);
	float halfMeter = (distance1 + distance2 + distance3) / 2;

	return sqrtf(halfMeter * (halfMeter - distance1) * (halfMeter - distance2) * (halfMeter - distance3));
}

bool Frame::checkPointInQuadrilateral(
	sf::Vector2f point,
	sf::Vector2f pointQuadrilateral1,
	sf::Vector2f pointQuadrilateral2,
	sf::Vector2f pointQuadrilateral3,
	sf::Vector2f pointQuadrilateral4)
{
	float squarePoint = 
		square(pointQuadrilateral1, pointQuadrilateral2, point) +
		square(pointQuadrilateral2, pointQuadrilateral3, point) +
		square(pointQuadrilateral3, pointQuadrilateral4, point) +
		square(pointQuadrilateral4, pointQuadrilateral1, point);
	
	float squareFigure =
		square(pointQuadrilateral1, pointQuadrilateral3, pointQuadrilateral2) +
		square(pointQuadrilateral1, pointQuadrilateral3, pointQuadrilateral4);

	if (squarePoint < squareFigure + 0.01f)
		return true;
	return false;
}

sf::Vector2f Frame::findIntersection(
	sf::Vector2f position11,
	sf::Vector2f position12,
	sf::Vector2f position21,
	sf::Vector2f position22)
{
	float k1 = (position12.y - position11.y) / (position12.x - position11.x);
	float k2 = (position22.y - position21.y) / (position22.x - position21.x);
	float b1 = position11.y - k1 * position11.x;
	float b2 = position21.y - k2 * position21.x;

	float interX = (b2 - b1) / (k1 - k2);
	float interY = k1 * interX + b1;

	return sf::Vector2(interX, interY);	
}

sf::Vector2f Frame::checkInterseption(sf::Vector2f position11, sf::Vector2f position12, sf::Vector2f position21, sf::Vector2f position22)
{
	sf::Vector2f interseptionPosition = findIntersection(
		position11, position12, position21, position22
	);

	int a[2];

	//a[1];
	//*(a + 1);

	if (checkPointInQuadrilateral(
		interseptionPosition,
		position11,
		position21,
		position12,
		position22))
	{
		return interseptionPosition;
	}

	return sf::Vector2f(0, 0);
}

void Frame::next()
{
	sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(*GameCycle::window);

	for (std::shared_ptr<Nextable> nextable : nextables)
	{
		nextable->next();
	}
}

void Frame::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (std::shared_ptr<sf::Drawable> drawable : drawables)
	{
		target.draw(*drawable);
	}
}
