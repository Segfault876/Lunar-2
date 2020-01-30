extern "C"{
    #include "lua/lua.h"
    #include "lua/lauxlib.h"
    #include "lua/lualib.h"
}
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <fstream>
#include <libgen.h>
#include "objects.hpp"

// Objects that must be declared in this header instead of main
extern SDL_Event event;
extern SDL_Window * window;
extern SDL_Renderer * renderer;
extern unsigned int channel;

//When deleting a texture from the vector, it is important to make sure
//that the location of the texture in the vector is replaced with NULL,
//To serve as a place holder, to prevent the locations from being shifted
extern std::vector<SDL_Texture *> textures;
