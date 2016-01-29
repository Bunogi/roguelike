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

extern std::string spritesWorld[];

extern std::string spritesEntities[];

class WorldObject {
	public:
		int x, y;
		bool solid;
		const int type;
		WorldObject(const int typeO = 0, int xPos = 0, int yPos = 0) : type(typeO){
			x = xPos;
			y = yPos;
		}
		virtual std::string getSprite() {
			return spritesWorld[type];
		}
};

class Entity : public WorldObject {
	public:
		World *worldClass;
		const int type;
		Entity(World *localWorld = nullptr, int xPos = 0, int yPos = 0, const int typeE = 1) : type(typeE) {
			worldClass = localWorld;
			x = xPos;
			y = yPos;
		}
		int hp;
		void update();
		const std::string name = "";
		std::string getSprite() {
			return spritesEntities[type];
		}

};
