#include "sdlclass.hpp"

#include "menu.hpp"

extern SDL *sdlClass;
extern const int gFontSize;

void Menu::draw() {
	switch (type) {
		case MenuType::inventory:
			int invHeight = 200;
			int invWidth = 400;
			sdlClass->drawRectFill({sdlClass->getWidth() - invWidth, sdlClass->getHeight() - invHeight, invWidth, invHeight},
				{0, 0, 0, 0xFF});

			break;
	}
}
