#pragma once

#include <string>

class World;

enum WorldObjectTypes : int {
	base = 0, 
	wall = 1,
	path
};

enum EntityTypes : int {
	angryHobo = 0,
	beggar = 1,
	player //Player is at the very bottom so it is guaranteed to be unique
};

extern char spritesWorld[];
extern char spritesEntities[];

extern std::string namesEntities[];

class WorldObject {
	public:
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

class Entity : public WorldObject {
	public:
		World *worldClass;
		const char type;
		std::string name;

		Entity(World *localWorld = nullptr, int xPos = 0, int yPos = 0, const char typeE = 1) : type(typeE) {
			worldClass = localWorld;
			x = xPos;
			y = yPos;
			switch (type) {
				case 'b': //Beggar
					hp = 2;
					strength = 0;
					name = "Beggar";
					break;
				case 'h': //Hobo
					hp = 3;
					strength = 1;
					name = "Angry Hobo";
					break;
			}
		}
		int hp;
		int strength; //Attack damage
		void update();
		std::string getSprite() {
			return std::string(1, type);
		}

		std::string getName() {
			return name;
		}

};
