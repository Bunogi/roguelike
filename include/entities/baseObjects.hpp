#pragma once

#include <string>

enum WorldObjectTypes : int {
	base = 0, 
	wall = 1,
	path,
};

enum EntityTypes {
	player = 0
};

extern std::string spritesWorld[];

extern std::string spritesEntities[];

class WorldObject {
	public:
		int x, y;
		bool solid;
		int type = 0;
		WorldObject(int typeO = 0, int xPos = 0, int yPos = 0) {
			x = xPos;
			y = yPos;
			type = typeO;
		}
		virtual std::string getSprite() {
			return spritesWorld[type];
		}
};

class Entity : public WorldObject {
	public:
		int hp;
		virtual void update() = 0;
		std::string getSprite() {
			return spritesEntities[type];
		}

};
