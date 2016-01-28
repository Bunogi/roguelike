#include <memory>
#include <string>

#include "sdlclass.hpp"

#include "messages.hpp"
#include "world.hpp"
#include "save.hpp"

World::World(SDL& localsdlclass) : player(this) {
	cameraX = cameraY = 0;
	sdlclass = &localsdlclass;

}

void World::update() {
	for (auto &i : entities) {
		i->update();
	}
	player.update();
	Messages::message = "x: " + std::to_string(player.x) + " y: " + std::to_string(player.y) + " cx: " + std::to_string(cameraX) + " cy: " + std::to_string(cameraY);
}

void World::draw() {
	for (auto &i : objects) {
		//Avoid drawing the player on top of already drawn world objects
		if (i->x == player.x and i->y == player.y)
			continue;

		sdlclass->print( (i->x + cameraX) * FONTSIZE, ((i->y + cameraY) * FONTSIZE) + FONTSIZE, i->getSprite());
	}
	
	sdlclass->print((player.x + cameraX) * FONTSIZE, ((player.y + cameraY) * FONTSIZE) + FONTSIZE, player.getSprite());
}

bool World::canMove(int x, int y) {
	for (auto &i : objects) {
		if (i->x == x and i->y == y) {
			if (isSolid(i->type))
				return false;
			else
				return true;
		}
	}
	return true;
}

bool World::isSolid(const WorldObject& object) {
	if (object.type == WorldObjectTypes::wall) {
		return true;
	}
	return false;
}


void World::scrollView(int dx, int dy) {
	cameraX += dx;
	cameraY += dy;
}

void World::getCameraPos(int *x, int *y) {
	if (x != nullptr) {
		*x = cameraX;
	}
	if (y != nullptr) {
		*y = cameraY;
	}
}
