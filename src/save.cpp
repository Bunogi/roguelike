#include <iostream>
#include <vector>
#include <memory>

#include <libconfig.h++>

#include "save.hpp"
#include "world.hpp"
#include "entities/baseObjects.hpp"

namespace Save {
	void loadMap() {
		try {
			libconfig::Config config;
			config.readFile("../defmap.cfg");
			const libconfig::Setting& root = config.getRoot();
			const libconfig::Setting& tiles = root["tiles"];

			if (tiles.isList()) {
				for (auto &tile : tiles) {
					Save::world->objects.push_back(std::unique_ptr<WorldObject>(new WorldObject(tile["type"], tile["x"], tile["y"])));
				}
			}
		}
		catch (libconfig::ParseException &ex) {
			std::cerr << "Libconfig error: " << ex.getError() << " on line " << ex.getLine();
		}
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

			root.add("map", libconfig::Setting::Type::TypeList);
			libconfig::Setting& worldTiles = root["map"];
			
			int i = 0;
			for (auto it = Save::world->objects.begin(); it != Save::world->objects.end(); it++) {
				worldTiles.add(libconfig::Setting::Type::TypeGroup);
				worldTiles[i].add("x", libconfig::Setting::Type::TypeInt);
				worldTiles[i]["x"] = (*it)->x;
				worldTiles[i].add("y", libconfig::Setting::Type::TypeInt);
				worldTiles[i]["y"] = (*it)->y;
				worldTiles[i].add("type", libconfig::Setting::Type::TypeInt);
				worldTiles[i]["type"] = (*it)->type;
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
				Save::world->objects.push_back(std::unique_ptr<WorldObject>(new WorldObject(i["type"], i["x"], i["y"])));
			}

		}
		catch (libconfig::ParseException &ex) {
			//TODO: Properly catch and deal with exceptions
		}
	} 
}
