#include "global.hpp"
#include "methods.hpp"

// Function CheckKeyPressed checks if a key is pressed
// Important note: characters on the lua side must be capitalized
int CheckKeyPressed(lua_State* L){ 
	int argc = lua_gettop(L);
	if (argc != 1){
		std::cout << "Error: CheckKeyPressed function requires 1 argument." << '\n';
	}

	const char* argv = luaL_checkstring(L,1);
	
	if (SDL_GetKeyboardState(NULL)[SDL_GetScancodeFromKey(SDL_GetKeyFromName(argv))]){
		lua_pushboolean(L,1);
	}else{
		lua_pushboolean(L,0);					
	}
	return 1;
}

// Function CheckKeyReleased checks if a key is released
// Important note: characters on the lua side must be capitalized
int CheckKeyReleased(lua_State* L){ 
	int argc = lua_gettop(L);
	if (argc != 1){
		std::cout << "Error: CheckKeyReleased function requires 1 argument." << '\n';
	}

	const char* argv = luaL_checkstring(L,1);

	if (SDL_GetKeyboardState(NULL)[SDL_GetScancodeFromKey(SDL_GetKeyFromName(argv))]){
		lua_pushboolean(L,0);
	}else{
		lua_pushboolean(L,1);					
	}
	return 1;
}

// Function CheckInstantKeyReleased returns true only once a key is released
// Returns false after that instant
int CheckInstantKeyReleased(lua_State* L){ 
	int argc = lua_gettop(L);
	if (argc != 1){
		std::cout << "Error: CheckInstantKeyReleased function requires 1 argument."  << '\n';
	}
	const char* argv = luaL_checkstring(L,1);

	if (event.type == SDL_KEYUP){
		if (strcmp(SDL_GetKeyName(event.key.keysym.sym),argv)==0){
			lua_pushboolean(L,1);
		}else{
			lua_pushboolean(L,0);					
		}
	}else{
		lua_pushboolean(L,0);
	}
	return 1;
}

// Function CheckInstantKeyPressed returns true only once a key is pressed
// Returns false after that instant
int CheckInstantKeyPressed(lua_State* L){ 
	int argc = lua_gettop(L);
	if (argc != 1){
		std::cout << "Error: CheckInstantKeyPressed function requires 1 argument."  << '\n';
	}
	const char* argv = luaL_checkstring(L,1);

	if (event.type == SDL_KEYDOWN){
		if (strcmp(SDL_GetKeyName(event.key.keysym.sym),argv)==0){
			lua_pushboolean(L,1);
		}else{
			lua_pushboolean(L,0);					
		}
	}else{
		lua_pushboolean(L,0);
	}
	return 1;
}


// Function CheckWindowClose is an optimized function for window loops
int CheckWindowClose(lua_State* L){

	if (event.type == SDL_QUIT){
		lua_pushboolean(L,1);
	}else{
		lua_pushboolean(L,0);
	}
	
	return 1;
}

int UpdateEvents(lua_State* L){
	int argc = lua_gettop(L);
	if (argc != 0){
		std::cout << "Error: UpdateEvents function requires 0 arguments."  << '\n';
	}
	SDL_PollEvent(&event);
	
	return 0;
}
