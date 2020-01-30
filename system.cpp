#include "global.hpp"
#include "methods.hpp"

int SetWindowTitle(lua_State* L){
	int argc = lua_gettop(L);
	if (argc != 1){
		std::cout << "Error: SetWindowTitle function requires 1 argument." << '\n';
	}

	SDL_SetWindowTitle(window,luaL_checkstring(L,1));
	
	return 0;
}

int SetWindowSize(lua_State* L){
	int argc = lua_gettop(L);
	if (argc != 2){
		std::cout << "Error: SetWindowSize function requires 2 arguments." << '\n';
	}

	SDL_SetWindowSize(window,luaL_checknumber(L,1),luaL_checknumber(L,2));

	return 0;
}

int Sleep(lua_State *L){
	// Check for correct number of arguments
	if (lua_gettop(L) != 1){
		std::cout << "Error: Sleep function requires 1 argument" << '\n';
	}    

    // usleep takes microseconds, multiply by a thousand for milliseconds 
	usleep(luaL_checknumber(L,1) * 1000);
	
    return 0;
}

// Function Collides performs basic AABB collision for sprites
int Collides(lua_State* L){
	// Check for correct number of arguments
	if (lua_gettop(L) != 2){
		std::cout << "Error: Collides function requires 2 arguments." << '\n';
	}
	
	// If we're passed a table, get CData for args 1 and 2
    if (lua_istable(L, 1)) {
        lua_getfield(L, 1, "CData");
        lua_replace(L, 1);
    }
    if (lua_istable(L, 2)) {
        lua_getfield(L, 2, "CData");
        lua_replace(L, 2);
    }
    
    // If args 1 and 2 do not exist pass an error
    if (!lua_touserdata(L, 1)){
        lua_error(L);
    }
    if (!lua_touserdata(L, 2)){
        lua_error(L);
    }
    
    // Dereference the sprites and check them for collision
    Sprite& ref1 = *(Sprite*)lua_touserdata(L, 1);
    Sprite& ref2 = *(Sprite*)lua_touserdata(L, 2);
	if (ref1.Collides(ref2)){
		lua_pushboolean(L,1);
	}else{
		lua_pushboolean(L,0);	
	}
	
    return 1;
}
