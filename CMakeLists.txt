cmake_minimum_required(VERSION 3.4.1 FATAL_ERROR)
project(roguelike)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
	if (CMAKE_COMPILER_IS_GNUCXX)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
	endif()
endif()

find_package(PkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} lib/SDL2)

set(TTF_SUPPORT ON)
add_subdirectory(lib/SDL2)
add_definitions(-DTTF_SUPPORT)

add_executable(
	rogue
	src/main.cpp
	src/messages.cpp
	src/world.cpp
	src/entities/player.cpp
)

target_link_libraries(rogue ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES} sdlclass)
