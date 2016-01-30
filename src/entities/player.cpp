#include "sdlclass.hpp"

#include "entities/baseObjects.hpp"
#include "world.hpp"
#include "messages.hpp"

World::Player::Player(World *localWorld, int xPos, int yPos) {
	worldClass = localWorld;
	x = xPos;
	y = yPos;
	strength = 1;
}

void World::Player::move(int dx, int dy) {
	Entity *monster = worldClass->checkEntity(x + dx, y + dy);
	if (monster != nullptr) { //There's a monster in the way!
		monster->hp -= strength; //Attack it

		std::string message = "You attack the ";
		message += monster->getName();
		message += "! It took " + std::to_string(strength) + " damage!";
		Messages::sendMessage(message);

		if (monster->hp <= 0) {
			message = "You have slain the " + monster->getName() + "!";
			Messages::sendMessage(message);
		}
		return;
	}
	
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

