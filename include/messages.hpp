#pragma once

#include <string>
#include <queue>

namespace Messages {
	extern std::queue<std::string> messages;
	void printMessage();
	void sendMessage(const std::string&& msg);
	void nextMessage();
}
