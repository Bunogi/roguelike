#pragma once

enum class MenuType {
	inventory
};

class Menu {
public:
	unsigned selection;
	unsigned selectionMax; 
	MenuType type;
	void draw();
	Menu(MenuType mType) {
		selection = 0;
		type = mType;
	};
};
