#include "global.hpp"
#include "methods.hpp"

int CreateSound(lua_State* L){
	// Check for correct number of arguments
	int argc = lua_gettop(L);
	if (argc != 1){
		std::cout << "Error: CreateSound function requires 1 argument." << '\n';
	}
	
	// Create the sound
	new (lua_newuserdata(L,sizeof(Sound))) Sound(luaL_checkstring(L,1),++channel);
	
	return 1;
}

int PlaySound(lua_State* L){
	//Check for correct number of arguemnts
	int argc = lua_gettop(L);
	if (argc!=1 && argc!=2){
		std::cout << "Error PlaySound function requires 1 or 2 arguments."  << '\n';
	}
	
	// If we're passed a table, get CData for args 1
    if (lua_istable(L, 1)) {
        lua_getfield(L, 1, "CData");
        lua_replace(L, 1);
    }
     
    // If arg 1 does not exist pass an error
    if (!lua_touserdata(L, 1)){
        lua_error(L);
    }
    
    Sound& ref = *(Sound*)lua_touserdata(L,1);
    if (argc == 2){
		if (lua_toboolean(L,2)==true){
			Mix_PlayChannel(ref.channel, ref.sound, -1);
		}else{
			Mix_PlayChannel(ref.channel, ref.sound, 0);
		}
	}else{
		Mix_PlayChannel(ref.channel, ref.sound, 0);
	}
	
	return 0;
}

int StopSound(lua_State* L){
	//Check for correct number of arguemnts
	int argc = lua_gettop(L);
	if (argc!=1){
		std::cout << "Error StopSound function requires 1 argument."  << '\n';
	}
	
	// If we're passed a table, get CData for args 1
    if (lua_istable(L, 1)) {
        lua_getfield(L, 1, "CData");
        lua_replace(L, 1);
    }
     
    // If arg 1 does not exist pass an error
    if (!lua_touserdata(L, 1)){
        lua_error(L);
    }
    
    Sound& ref = *(Sound*)lua_touserdata(L,1);
	Mix_HaltChannel(ref.channel);
	
	return 0;
}

int PauseSound(lua_State* L){
	//Check for correct number of arguemnts
	int argc = lua_gettop(L);
	if (argc!=1){
		std::cout << "Error PauseSound function requires 1 argument."  << '\n';
	}
	
	// If we're passed a table, get CData for args 1
    if (lua_istable(L, 1)) {
        lua_getfield(L, 1, "CData");
        lua_replace(L, 1);
    }
     
    // If arg 1 does not exist pass an error
    if (!lua_touserdata(L, 1)){
        lua_error(L);
    }
    
    Sound& ref = *(Sound*)lua_touserdata(L,1);
	Mix_Pause(ref.channel);
	
	return 0;
}
