#include <memory>
#include <string>

#include "sdlclass.hpp"

#include "screen.hpp"
#include "world.hpp"
#include "messages.hpp"
#include "entities/player.hpp"

World::World(SDL& localsdlclass) : player(this) {
	cameraX = cameraY = 0;
	sdlclass = &localsdlclass;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			objects.push_back(std::unique_ptr<WorldObject>(new WorldObject(i + 2, j + 2)));
		}
	}

	objects.push_back(std::unique_ptr<WorldObject>(new WorldObject(100, 0)));

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
		sdlclass->print( (i->x + cameraX) * FONTSIZE, ((i->y + cameraY) * FONTSIZE) + FONTSIZE, i->getSprite());
	}
	for (auto &i : entities) {
		i->update();
	}
	
	sdlclass->print((player.x + cameraX) * FONTSIZE, ((player.y + cameraY) * FONTSIZE) + FONTSIZE, player.getSprite());
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
