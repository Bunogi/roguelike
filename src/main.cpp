#include <string>
#include <iostream>

#include "SDL.h"
#include "sdlclass.hpp"

#include "messages.hpp"
#include "save.hpp"
#include "world.hpp"
#include "input.hpp"

World *Save::world;
SDL *sdlClass;
int gFontSize = 20;

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <path-to-font>\n";
		return 1;
	}

	try {
		sdlClass = new SDL(1366, 768);
		sdlClass->setRenderClearColour({0, 0, 0, 0xFF});
		
		sdlClass->loadFont(std::string(argv[1]), gFontSize);

		bool quit = false;
		World world;
		Save::world = &world;
		Save::loadMap();
		SDL_Event event;
		while (not quit) {
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_QUIT: 
						quit = true;
						break;
					case SDL_KEYDOWN:
						Input::handleGameInput(event.key.keysym.sym, world);
						break;
					}
				}
			
			sdlClass->clearRenderer();
			Messages::printMessage();
			world.draw();
			sdlClass->renderPresent();
		}
		delete sdlClass;
	}
	catch (SDLException &ex) {
		ex.printError();
		delete sdlClass;
	}
}
