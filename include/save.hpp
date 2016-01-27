#pragma once

#include "world.hpp"

namespace Save {
	extern void loadMap();
	extern void quickSave();
	extern void quickLoad();
	extern World* world;
};
