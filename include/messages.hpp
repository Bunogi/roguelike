#pragma once

#include <string>
#include <queue>

#include "sdlclass.hpp"

namespace Messages {
	extern std::queue<std::string> messages;
	void printMessage(SDL& sdlclass);
	void sendMessage(std::string msg);
	void nextMessage();
}
