#include "entities/baseObjects.hpp"
#include "world.hpp"

void Entity::update() {
	int px = worldClass->player.x;
	int py = worldClass->player.y;

	if (px > x and worldClass->canMove(x + 1, y))
		x++;
	else if (px < x and worldClass->canMove(x - 1, y))
		x--;
	
	if (py > y and worldClass->canMove(x, y + 1))
		y++;
	else if (py < y and worldClass->canMove(x, y - 1))
		y--;
}
