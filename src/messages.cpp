#include "sdlclass.hpp"

#include "messages.hpp"

namespace Messages {
	std::string message = "h";
	void printMessage(SDL& sdlclass) {
		sdlclass.print(0, 0, message);
	}
}
