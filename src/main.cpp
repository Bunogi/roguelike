#include <string>
#include <iostream>

#include "SDL.h"
#include "sdlclass.hpp"

#include "messages.hpp"
#include "save.hpp"
#include "world.hpp"

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
						switch (event.key.keysym.sym) {
							case SDLK_KP_7:
								world.player.move(-1, -1);
								break;
							case SDLK_KP_8:
								world.player.move(0, -1);
								break;
							case SDLK_KP_9:
								world.player.move(1, -1);
								break;
							case SDLK_KP_4:
								world.player.move(-1, 0);
								break;
							case SDLK_KP_5:
								//Stand still goes here
								break;
							case SDLK_KP_6:
								world.player.move(1, 0);
								break;
							case SDLK_KP_1:
								world.player.move(-1, 1);
								break;
							case SDLK_KP_2:
								world.player.move(0, 1);
								break;
							case SDLK_KP_3:
								world.player.move(1, 1);
								break;
							case SDLK_F5:
								Save::quickSave();
								break;
							case SDLK_F9:
								//Quickload
								break;
						}
						break;
					}
				}
			
			sdlclass.clearRenderer();
			Messages::printMessage(sdlclass);
			world.update();
			world.draw();
			sdlclass.renderPresent();
		}
	}
	catch (SDLException &ex) {
		ex.printError();
	}
	
}
