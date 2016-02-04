#include "sdlclass.hpp"

#include "entities/objects.hpp"
#include "world.hpp"
#include "messages.hpp"

extern SDL *sdlClass;
extern const int gFontSize;

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

		Messages::sendMessage("You attack the " + monster->name + "! It took " +  std::to_string(strength) + " damage!");

		if (monster->hp <= 0) 
			Messages::sendMessage("You have slain the " + monster->name + "!");
		return;
	}
	
	if (worldClass->canMove(x + dx, y + dy)) {
		x += dx;
		y += dy;
	}

	int camX, camY;
	int camW, camH;
	worldClass->getCameraPos(&camX, &camY);
	camW = sdlClass->getWidth() / gFontSize;
	camH = sdlClass->getHeight() / gFontSize;
	
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

int World::Player::attack(int damage) {
	//TODO: Defence and damage resistance and all that good stuff
	//std::cerr << "Player attacked!\n";
	hp -= damage;
	return hp;
}

void World::Player::pickupItem(std::vector<Item*>& itemList) {
	for (auto it = itemList.begin(); it != itemList.end(); ) {
		if ((*it)->x == x and (*it)->y == y) {
			inventory.push_back({(*it)->type, (*it)->quantity});
			Messages::sendMessage("You picked up " + std::to_string((*it)->quantity) + " " + (*it)->name);

			delete *it;
			it = itemList.erase(it);
			return;
		}
		else
			it++;
	}

	Messages::sendMessage("There's nothing here to pick up!");
}

