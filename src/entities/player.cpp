#include "sdlclass.hpp"

#include "world.hpp"

World::Player::Player(World *localWorld, int xPos, int yPos) {
	worldClass = localWorld;
	x = xPos;
	y = yPos;
}

void World::Player::move(int dx, int dy) {
	if (worldClass->canMove(x + dx, y + dy)) {
		x += dx;
		y += dy;
	}

	int camX, camY;
	int camW, camH;
	worldClass->getCameraPos(&camX, &camY);
	camW = worldClass->sdlclass->getWidth() / FONTSIZE;
	camH = worldClass->sdlclass->getHeight() / FONTSIZE;
	
	if (x + camX < 5 ) {
		worldClass->scrollView(5);
	}
	else if (x + camX > camW - 5) {
		worldClass->scrollView(-5);
	}
	
	if (y + camY < 5) {
		worldClass->scrollView(0, 5);
	}
	else if (y + camY > camH - 5) {
		worldClass->scrollView(0, -5);
	}

}

void World::Player::update() {

}

