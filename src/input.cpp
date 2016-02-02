#include "SDL.h"

#include "input.hpp"
#include "world.hpp"
#include "save.hpp"
#include "messages.hpp"

namespace Input {
	void handleInput(SDL_Keycode& key, World& world) {
			if (Messages::messages.size() >= 1) {
				Messages::nextMessage();
				return;
			}

			bool timePassed = true;
			switch (key) {
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
					//Stand still
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
					timePassed = false;
					break;
				case SDLK_F9:
					Save::quickLoad();
					timePassed = false;
					break;
				default:
					timePassed = false;
			}
			if (timePassed) {
				world.update();
				Messages::nextMessage();
			}
	}
}
