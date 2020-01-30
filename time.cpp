#include "global.hpp"
#include "methods.hpp"

int TickClock(lua_State* L){
	int argc = lua_gettop(L);
	if (argc != 1){
		std::cout << "Error: TickClock function requires 1 argument."  << '\n';
	}
	if (lua_istable(L, 1)) {
        lua_getfield(L, 1, "CData");
        lua_replace(L, 1);
    }
    if (!lua_touserdata(L, 1)){
        lua_error(L);
    }
    Clock& ref1 = *(Clock*)lua_touserdata(L, 1);
    ref1.currentTime = ref1.lastTime;
	ref1.lastTime = SDL_GetTicks();
	lua_pushinteger(L,ref1.lastTime-ref1.currentTime);
	return 1;
}

int CreateClock(lua_State* L){
	int argc = lua_gettop(L);
	if (argc != 0){
		std::cout << "Error: CreateClock function requires 0 arguments."  << '\n';
	}
	new (lua_newuserdata(L,sizeof(Clock))) Clock();
	return 1;	
}
