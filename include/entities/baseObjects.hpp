#pragma once

#include <string>

class WorldObject {
	public:
		int x, y;
		bool solid;
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
