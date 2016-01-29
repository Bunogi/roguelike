#include <string>
#include <iostream>

#include "SDL.h"
#include "sdlclass.hpp"

#include "messages.hpp"
#include "save.hpp"
#include "world.hpp"
#include "input.hpp"

World * Save::world;

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <path-to-font>\n";
		return 1;
	}

	try {
		SDL sdlclass(1366, 768);
		sdlclass.setRenderClearColour({0, 0, 0, 0xFF});
		
		sdlclass.loadFont(std::string(argv[1]), FONTSIZE);

		bool quit = false;
		World world(sdlclass);
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
						Input::handleInput(event.key.keysym.sym, world);
						break;
					}
				}
			
			sdlclass.clearRenderer();
			Messages::printMessage(sdlclass);
			world.draw();
			sdlclass.renderPresent();
		}
	}
	catch (SDLException &ex) {
		ex.printError();
	}
	
}
