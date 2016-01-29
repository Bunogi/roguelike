#pragma once

#include "SDL.h"

#include "world.hpp"

namespace Input {
	extern void handleInput(SDL_Keycode& key, World& world);
	//extern void loadInput(); //Load input configuration
}
