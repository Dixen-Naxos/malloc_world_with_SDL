cmake_minimum_required(VERSION 3.20)
project(malloc_world_with_SDL C)

set(CMAKE_C_STANDARD 99)

set(SDL2_DIR "ext/SDL2/lib/cmake/SDL2/")
find_library(SDL2 NAMES mingw32 SDL2main SDL2 SDL2_image SDL2_ttf HINTS "ext/SDL2/lib" PATH_SUFFIXES "ext/SDL2/lib/cmake/SDL2/" "ext/SDL2/lib/pkgconfig")
find_package(SDL2 REQUIRED)
include_directories(ext/SDL2/include)

include_directories(
        src/include
        )


add_executable(malloc_world_with_SDL
        src/inventory.c
        src/battles.c
        src/items.c
        src/player.c
        src/save.c
        src/map.c
        src/move.c
        src/cli.c
        src/main.c
        src/monsters.c
        src/pnj.c
        src/structures.c
        src/sdl_functions.c)

