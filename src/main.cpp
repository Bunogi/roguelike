#include <string>
#include <iostream>

#include "SDL.h"
#include "sdlclass.hpp"

#include "messages.hpp"
#include "world.hpp"

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
		SDL_Event event;
		while (not quit) {
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_QUIT: 
						quit = true;
						break;
					case SDL_KEYDOWN:
						switch (event.key.keysym.sym) {
							case SDLK_UP:
								world.player.move(0, -1);
								break;
							case SDLK_DOWN:
								world.player.move(0, 1);
								break;
							case SDLK_LEFT:
								world.player.move(-1, 0);
								break;
							case SDLK_RIGHT:
								world.player.move(1, 0);
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
