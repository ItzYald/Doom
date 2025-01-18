#include "PositionHavier.h"

float PositionHavier::distanceTo(sf::Vector2f objectPosition)
{
	float dX = objectPosition.x - position.x;
	float dY = objectPosition.y - position.y;

	return sqrtf(dX * dX + dY * dY);
}
