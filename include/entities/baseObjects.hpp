#pragma once

#include <string>

enum WorldObjectTypes {
	base = 0
};

enum EntityTypes {
	player = 0
};

class WorldObject {
	public:
		int x, y;
		bool solid;
		int type = 0;
		WorldObject(int xPos = 0, int yPos = 0) {
			x = xPos;
			y = yPos;
		}
		virtual std::string getSprite() {
			return "`";
		}
};

class Entity : public WorldObject {
	public:
		int hp;
		virtual void update() = 0;
		virtual std::string getSprite() {
			return "0";
		}
};
