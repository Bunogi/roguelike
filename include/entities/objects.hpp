#pragma once

#include <string>

class World;

enum ItemType : int {
	food = 0,
	torch = 1
};

enum WorldObjectTypes : int {
	base = 0, 
	wall = 1,
	path
};

enum EntityTypes : int {
	angryHobo = 0,
	beggar = 1
};

extern char spritesWorld[];
extern char spritesEntities[];

extern std::string namesEntities[];
extern std::string namesItems[];

struct WorldObject {
	int x, y;
	bool solid;
	const char type;
	WorldObject(const char typeO = 0, int xPos = 0, int yPos = 0) : type(typeO) {
		x = xPos;
		y = yPos;
	}
	virtual std::string getSprite() {
		return std::string(1, type);
	}
};

struct Entity : public WorldObject {
	World *worldClass;
	const int type;
	std::string name;

	Entity(World *localWorld = nullptr, int xPos = 0, int yPos = 0, const int typeE = 1) : type(typeE) {
		worldClass = localWorld;
		x = xPos;
		y = yPos;
		switch (type) {
			case EntityTypes::beggar:
				hp = 2;
				strength = 0;
				name = "Beggar";
				break;
			case EntityTypes::angryHobo: 
				hp = 4;
				strength = 1;
				name = "Angry Hobo";
				break;
		}
	}
	int hp;
	int strength; //Attack damage
	void update();
	std::string getSprite() {
		return std::string(1, spritesEntities[type]);
	}
};

struct Item : public WorldObject {
	const int type;
	int quantity;
	std::string& name;
	std::string sprite;

	Item(const int typeI, int xPos, int yPos, int qty = 1) : type(typeI), name(namesItems[type]) {
		x = xPos;
		y = yPos;
		quantity = qty;
		sprite = "?";
	};
};
