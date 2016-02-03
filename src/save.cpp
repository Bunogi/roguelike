#include <iostream>
#include <vector>
#include <fstream>

#include <libconfig.h++>

#include "save.hpp"
#include "world.hpp"
#include "entities/objects.hpp"

namespace Save {
	void loadMap() {
		std::ifstream map;
		map.open("../town.map");
		if (not map.is_open()) {
			std::cerr << "Failed to load map\n";
			return;
		}

		std::string line;
		int x = 0, y = 0;
		while (std::getline(map, line)) {
			for (auto &i : line) {
				for (int j = 0; spritesWorld[j] != '\0'; j++) {
					if (i == spritesWorld[j]) {
						Save::world->objects.push_back(new WorldObject(i, x, y));
						break;
					}
				}
				x++;
			}
			x = 0;
			y++;
		}

		//try {
			libconfig::Config config;
			config.readFile("../town.things");

			const libconfig::Setting& root = config.getRoot();
			const libconfig::Setting& entities = root["entities"];

			for (auto &i : entities) {
				Save::world->entities.push_back(new Entity(Save::world, i["x"], i["y"], i["type"]));
			}

			const libconfig::Setting& items = root["items"];
			for (auto &i : items) {
				Save::world->items.push_back(new Item(i["type"], i["x"], i["y"]));
			}
		//}
	}

	void quickSave() {
		try {
			libconfig::Config config;

			libconfig::Setting& root = config.getRoot();

			root.add("camera", libconfig::Setting::Type::TypeGroup);
			libconfig::Setting& camera = root["camera"];
			int camX, camY;
			Save::world->getCameraPos(&camX, &camY);
			camera.add("x", libconfig::Setting::Type::TypeInt);
			camera["x"] = camX;
			camera.add("y", libconfig::Setting::Type::TypeInt);
			camera["y"] = camY;

			root.add("player", libconfig::Setting::Type::TypeGroup);
			libconfig::Setting& playerConf = root["player"];
			playerConf.add("x", libconfig::Setting::Type::TypeInt);
			playerConf["x"] = Save::world->player.x;
			playerConf.add("y", libconfig::Setting::Type::TypeInt);
			playerConf["y"] = Save::world->player.y;
			playerConf.add("items", libconfig::Setting::TypeList);

			libconfig::Setting& playerItems = playerConf["items"];

			int i = 0;
			for (auto it = Save::world->player.inventory.begin(); it != Save::world->player.inventory.end(); it++) {
				playerItems.add(libconfig::Setting::Type::TypeGroup);
				playerItems[i].add("type", libconfig::Setting::Type::TypeInt);
				playerItems["type"] = it->type;
				playerItems[i].add("quantity", libconfig::Setting::Type::TypeInt);
				playerItems["quantity"] = it->quantity;
				i++;
			}


			root.add("map", libconfig::Setting::Type::TypeList);
			libconfig::Setting& worldTiles = root["map"];

			i = 0;
			for (auto it = Save::world->objects.begin(); it != Save::world->objects.end(); it++) {
				worldTiles.add(libconfig::Setting::Type::TypeGroup);
				worldTiles[i].add("x", libconfig::Setting::Type::TypeInt);
				worldTiles[i]["x"] = (*it)->x;
				worldTiles[i].add("y", libconfig::Setting::Type::TypeInt);
				worldTiles[i]["y"] = (*it)->y;
				worldTiles[i].add("type", libconfig::Setting::Type::TypeInt);
				worldTiles[i]["type"] = static_cast<int>((*it)->type);
				i++;
			}

			root.add("monsters", libconfig::Setting::Type::TypeList);
			libconfig::Setting& monsters = root["monsters"];

			i = 0;
			for (auto it = Save::world->entities.begin(); it != Save::world->entities.end(); it++) {
				monsters.add(libconfig::Setting::Type::TypeGroup);
				monsters[i].add("x", libconfig::Setting::Type::TypeInt);
				monsters[i]["x"] = (*it)->x;
				monsters[i].add("y", libconfig::Setting::Type::TypeInt);
				monsters[i]["y"] = (*it)->y;
				monsters[i].add("type", libconfig::Setting::Type::TypeInt);
				monsters[i]["type"] = static_cast<int>((*it)->type);
				i++;
			}

			root.add("items", libconfig::Setting::Type::TypeList);
			libconfig::Setting& items = root["items"];

			i = 0;
			for (auto it = Save::world->items.begin(); it != Save::world->items.end(); it++) {
				items.add(libconfig::Setting::Type::TypeGroup);
				items[i].add("x", libconfig::Setting::Type::TypeInt);
				items[i]["x"] = (*it)->x;
				items[i].add("y", libconfig::Setting::Type::TypeInt);
				items[i]["y"] = (*it)->y;
				items[i].add("type", libconfig::Setting::Type::TypeInt);
				items[i]["type"] = static_cast<int>((*it)->type);
				items[i].add("quantity", libconfig::Setting::Type::TypeInt);
				items[i]["quantity"] = (*it)->quantity;
				i++;
			}

			config.writeFile("../quickSave");
		}
		//TODO: Properly catch and deal with exceptions
		catch (libconfig::SettingTypeException &ex) {
			std::cerr << "Libconfig error: Wrong setting type for setting " << ex.getPath() << "\n";
		}
	}

	void quickLoad() {
		try {
			libconfig::Config config;
			config.readFile("../quickSave");

			const libconfig::Setting& root = config.getRoot();
			const libconfig::Setting& camera = root["camera"];

			int camX, camY;
			Save::world->getCameraPos(&camX, &camY);
			Save::world->scrollView(-camX, -camY);

			Save::world->scrollView(camera["x"], camera["y"]);

			const libconfig::Setting& player = root["player"];
			Save::world->player.x = player["x"];
			Save::world->player.y = player["y"];

			const libconfig::Setting& world = root["map"];
			Save::world->objects.clear(); 

			for (auto &i : world) {
				int type;
				i.lookupValue("type", type);
				Save::world->objects.push_back(new WorldObject(type, i["x"], i["y"]));
			}

			const libconfig::Setting& monsters = root["monsters"];
			Save::world->entities.clear();

			for (auto &i : monsters) {
				Save::world->entities.push_back(new Entity(Save::world, i["x"], i["y"], i["type"]));
			}

			const libconfig::Setting& items = root["items"];
			Save::world->items.clear();

			for (auto &i : items) {
				Save::world->items.push_back(new Item(i["type"], i["x"], i["y"], i["quantity"]));
			}

		}
		catch (libconfig::ParseException &ex) {
			//TODO: Properly catch and deal with exceptions
		}
	} 
}

