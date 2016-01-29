#pragma once

#include <vector>
#include <memory>

#include "sdlclass.hpp"

#include "entities/baseObjects.hpp"

#define FONTSIZE 20

class World {
	std::vector<std::unique_ptr<Entity> > entities;

	int cameraX, cameraY; //Left hand corner of the camera relative to the origin of the map

	SDL* sdlclass;

	public:
		std::vector<std::unique_ptr<WorldObject> > objects;
		World(SDL& localsdlclass);
		void update(); //Updates Every entity on screen, to be called every time we recieve input
		void draw(); //Draws the screen
		void getCameraPos(int *x, int *y);
		void scrollView(int x, int y = 0); //Scroll the view
		bool canMove(int x, int y); //Check whenever or not an entity can move to location (x,y)
		bool isSolid(const WorldObject& object); //Finds out if an object is solid or not

		class Player : public Entity {
			public:
				Player(World *localWorld,int xPos = 0, int yPos = 0);
				void update();
				void move(int dx, int dy = 0);
				std::string getSprite() {
					return "@";
				}
		};

		Player player; //Stores the player
};
