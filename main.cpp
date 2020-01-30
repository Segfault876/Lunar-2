#define SDL_MAIN_HANDLED 
#include "global.hpp"
#include "methods.hpp"

/**
* Lunar Engine
* V. Alpha 0.2
* Nick Panagakis (Copyright)
*/

int main(int argc, char* argv[]){
	// Initialize SDL and create a window
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF);
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    window = SDL_CreateWindow("Lunar Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_OPENGL); 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == NULL) {
        std::cout << "Could not create window: %s\n" << SDL_GetError() << std::endl;
        return 1;
    }else if (argc < 2){
		std::cout << "Expected a filename argument." << std::endl;
		return 1;
	}
   	SDL_RenderClear(renderer);
	
    // Create new Lua state
    lua_State *lua_state;
    lua_state = luaL_newstate();
    
    // Load Lua libraries
    static const luaL_Reg lualibs[]={
        { "base", luaopen_base },
        { NULL, NULL}
    };
    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++){
        lib->func(lua_state);
        lua_settop(lua_state, 0);
    }
	luaL_openlibs(lua_state);
	
	// Load main Lua file
    luaL_loadfile(lua_state, argv[1]);

	// Chdir to source's directory
	chdir(dirname(argv[1]));
    
	// Register engine functions for Lua
	lua_register(lua_state, "CreateFont",CreateFont);
	lua_register(lua_state, "CreateText",CreateText);
	lua_register(lua_state, "DrawText",DrawText);
	lua_register(lua_state, "PauseSound",PauseSound);
	lua_register(lua_state, "StopSound",StopSound);
	lua_register(lua_state, "PlaySound",PlaySound);
	lua_register(lua_state, "CreateSound",CreateSound);
	lua_register(lua_state, "GetSpriteTexture",GetSpriteTexture);
	lua_register(lua_state, "SetSpriteTexture",SetSpriteTexture);
	lua_register(lua_state, "CreateClock",CreateClock);
	lua_register(lua_state, "SetWindowTitle",SetWindowTitle);
	lua_register(lua_state, "SetWindowSize",SetWindowSize);
	lua_register(lua_state, "TickClock",TickClock);
	lua_register(lua_state, "UpdateEvents",UpdateEvents);
	lua_register(lua_state, "GetSpritePosition",GetSpritePosition);
	lua_register(lua_state, "SetSpritePosition",SetSpritePosition);	
	lua_register(lua_state, "CheckKeyReleased",CheckKeyReleased);
	lua_register(lua_state, "CheckInstantKeyReleased",CheckInstantKeyReleased);	
	lua_register(lua_state, "CheckKeyPressed",CheckKeyPressed);
	lua_register(lua_state, "CheckInstantKeyPressed",CheckInstantKeyPressed);
    lua_register(lua_state, "CheckWindowClose",CheckWindowClose);
    lua_register(lua_state, "CreateSprite",CreateSprite);
    lua_register(lua_state, "Collides",Collides);
    lua_register(lua_state, "DrawSprite",DrawSprite);
    lua_register(lua_state, "CreateTexture",CreateTexture);
    lua_register(lua_state, "ClearDisplay",ClearDisplay);
    lua_register(lua_state, "UpdateDisplay",UpdateDisplay);
    lua_register(lua_state, "Sleep",Sleep);

    // Check for errors
	if (lua_pcall(lua_state, 0, 0, 0)){
		std::cout << "Lua Error: " <<  lua_tostring(lua_state, -1);
		lua_pop(lua_state,1);
  	}		

	std::cout << "Program terminated.";
  	
  	// Quit SDL and close Lua
    lua_close(lua_state);
   	SDL_Quit(); 
   	
   	return 0;
}
