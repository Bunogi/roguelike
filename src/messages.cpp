#include <string>
#include <queue>

#include "sdlclass.hpp"

#include "messages.hpp"

namespace Messages {
	std::queue<std::string> messages;
	std::string text = " ";
	void printMessage(SDL& sdlclass) {
		sdlclass.print(0, 0, text);
	}

	void sendMessage(const std::string msg) {
		messages.push(msg);
	}

	void nextMessage() {
		int size = messages.size();
		if (size == 0)
			text = " ";
		else if (size == 1) {
			text = messages.front();
			messages.pop();
		}
		else if (size > 1) {
			text = messages.front() + " [more..]";
			messages.pop();
		}
	}
}
