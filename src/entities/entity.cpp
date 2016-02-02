#include <iostream>
#include <cmath>
#include <string>

#include "entities/objects.hpp"
#include "world.hpp"
#include "messages.hpp"

void Entity::update() {
	int px = worldClass->player.x;
	int py = worldClass->player.y;

	if (std::abs(x - px) < 2 and std::abs(y - py) < 2) {
		//TODO: Add accuracy
		worldClass->player.attack(strength);
		std::string message = "The " + getName() + " attacks you! You take " + std::to_string(strength) + " damage!";
		Messages::sendMessage(message);
		return;
	}

	if (px > x and worldClass->canMove(x + 1, y))
		x++;
	else if (px < x and worldClass->canMove(x - 1, y))
		x--;
	if (py > y and worldClass->canMove(x, y + 1))
		y++;
	else if (py < y and worldClass->canMove(x, y - 1))
		y--;
}
