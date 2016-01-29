cmake_minimum_required(VERSION 3.4.1 FATAL_ERROR)
project(roguelike)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")

find_package(PkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf)
pkg_search_module(CONFIG++ REQUIRED libconfig++)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} lib/SDL2)

set(TTF_SUPPORT ON)
add_subdirectory(lib/SDL2)
add_definitions(-DTTF_SUPPORT)

add_executable(
	rogue
	src/main.cpp
	src/messages.cpp
	src/world.cpp
	src/save.cpp
	src/sprites.cpp
	src/input.cpp
	src/entities/player.cpp
	src/entities/entity.cpp
)

target_link_libraries(rogue ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES} ${CONFIG++_LIBRARIES} sdlclass)
