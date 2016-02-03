#pragma once

#include <vector>

#include "sdlclass.hpp"

#include "entities/objects.hpp"

#define FONTSIZE 20

class World {
	int cameraX, cameraY; //Left hand corner of the camera relative to the origin of the map

	SDL* sdlclass;

	public:
		std::vector<WorldObject*> objects;
		std::vector<Entity*> entities;
		std::vector<Item*> items;
		World(SDL& localsdlclass);
		void update(); //Updates Every entity on screen, to be called every time we recieve input
		void draw(); //Draws the screen
		void getCameraPos(int *x, int *y);
		void scrollView(int x, int y = 0); //Scroll the view
		Entity *checkEntity(int x, int y); //Check if there's an entity in (x, y)
		Item *checkItem(int x, int y); //Check if there's an item in  (x, y)
		bool canMove(int x, int y); //Check whenever or not an entity can move to location (x,y)
		bool isSolid(const WorldObject& object); //Finds out if an object is solid or not

		struct Player : public Entity {
			struct InventoryItem {
				int quantity;
				const int type;
				std::string& name;
				InventoryItem(int typeI, int qty) : type(typeI), name(namesItems[typeI]) {
					quantity = qty;
					name = namesItems[typeI];
				}
			};
			std::vector<InventoryItem> inventory;
			Player(World *localWorld,int xPos = 0, int yPos = 0);
			void update();
			void move(int dx, int dy = 0);
			void pickupItem(std::vector<Item*>& itemList);
			int attack(int damage);

			std::string getSprite() {
				return "@";
			}
		};

		Player player; //Stores the player
};
