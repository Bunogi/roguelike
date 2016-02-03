#Hello, world!
This is a roguelike.. Well, it's starting to look like one, anyway.

#Implemented so far
	- Functional enemies, very basic AI
	- Items you can pick up
	- Very basic combat system

#Controls
	- Numpad for movement, 5 stands still
	- 'g' to pick stuff up
	- F5 for quicksave
	- F9 to quickload

#Building
##You'll need:
	- A compiler with C++11 support
	- SDL2 and SDL2TTF installed
	- Libconfig installed
	- CMake
	- Some TTF font for the graphics

##Steps: 
```bash
git submodule init && git submodule update; #To download my SDL2 wrapper class
mkdir build && cd build; 
cmake ..  && make;
```
If you get linker errors about undefined references, try running `cmake .. && make` one more time. Not sure why this is sometimes required. 
