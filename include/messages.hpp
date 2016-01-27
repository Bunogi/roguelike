#pragma once

#include <string>

#include "sdlclass.hpp"

namespace Messages {
	extern std::string message;
	void printMessage(SDL& sdlclass);
	bool sendMessage(std::string& msg);
}
