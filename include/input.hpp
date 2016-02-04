#pragma once

#include "SDL.h"

#include "world.hpp"

namespace Input {
	extern void handleGameInput(SDL_Keycode& key, World& world);
	//extern void handleMenuInput(SDL_Keycode& key, Menu& menu);
}
