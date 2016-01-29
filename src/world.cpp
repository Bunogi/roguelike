#include <memory>
#include <string>
#include <vector>

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
	//Messages::message = "x: " + std::to_string(player.x) + " y: " + std::to_string(player.y) + " cx: " + std::to_string(cameraX) + " cy: " + std::to_string(cameraY);
}

void World::draw() {
	struct Point {
		int x, y;
	};

	std::vector<Point> drawnEntities;

	for (auto &i : entities) {
		sdlclass->print((i->x + cameraX) * FONTSIZE, ((i->y + cameraY) * FONTSIZE) + FONTSIZE, i->getSprite());
		drawnEntities.push_back({i->x, i->y});
	}

	for (auto &i : objects) {
		bool print = true;

		//Determine if we've drawn anything at these spots before
		for (auto &j : drawnEntities) {
			if (j.x == i->x and j.y == i->y) {
				print = false;
				break;
			}
		}

		if (i->x == player.x and i->y == player.y)
			print = false;

		if(print) //Only draw the objects in spots where we haven't drawn anything
			sdlclass->print((i->x + cameraX) * FONTSIZE, ((i->y + cameraY) * FONTSIZE) + FONTSIZE, i->getSprite());
	}

	
	sdlclass->print((player.x + cameraX) * FONTSIZE, ((player.y + cameraY) * FONTSIZE) + FONTSIZE, player.getSprite());
}

bool World::canMove(int x, int y) {
	//Check if player occupies the specified spot
	if (player.x == x and player.y == y)
		return false;

	//Is there an entity in the way?
	for (auto &i : entities) {
		if (i->x == x and i->y == y)
			return false;
	}

	//Is there a solid object here?
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
