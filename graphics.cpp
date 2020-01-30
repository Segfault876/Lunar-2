#include "global.hpp"
#include "methods.hpp"

int GetSpriteTexture(lua_State* L){
	// Check for correct number of arguments
	if (lua_gettop(L) != 1){
		std::cout << "Error: GetSpriteTexture function requires 1 argument." << '\n';
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
    
    Sprite& ref = *(Sprite*)lua_touserdata(L, 1);
	lua_pushinteger(L,ref.texture);

    return 1;
}
    
int ClearDisplay(lua_State* L){
	// Check for correct number of arguments
	if (lua_gettop(L) != 0){
		std::cout << "Error: Clear function requires 0 arguments." << '\n';
	}
	
	// Clear all textures rendered
	SDL_RenderClear(renderer);
	
	return 0;
}

int UpdateDisplay(lua_State* L){
	// Check for correct number of arguments
	if (lua_gettop(L) != 0){
		std::cout << "Error: UpdateDisplay function requires 0 arguments." << '\n';
	}

	// Update the display	
    SDL_RenderPresent(renderer);
	
	return 0;
}

int SetSpriteTexture(lua_State* L){
	// Check for correct number of arguments
	if (lua_gettop(L) != 2){
		std::cout << "Error: SetSpriteTexture function requires 2 arguments." << '\n';
	}
	
	// If we're passed a table, get CData for arg 1
    if (lua_istable(L, 1)) {
        lua_getfield(L, 1, "CData");
        lua_replace(L, 1);
    }
    
    // If arg 1 does not exist pass an error
    if (!lua_touserdata(L, 1)){
        lua_error(L);
    }
    
    Sprite& ref = *(Sprite*)lua_touserdata(L,1);
	ref.texture = luaL_checknumber(L,2);
    return 0;
}

int GetSpritePosition(lua_State* L){
	// Check for correct number of arguments
	if (lua_gettop(L) != 1){
		std::cout << "Error: GetSpritePosition function requires 1 argument." << '\n';
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
    
    // Dereference the sprite and check them for collision
    Sprite& ref1 = *(Sprite*)lua_touserdata(L, 1);
	lua_pushinteger(L,ref1.x);
	lua_pushinteger(L,ref1.y);

    return 2;
}

int SetSpritePosition(lua_State* L){
	// Check for correct number of arguments
	if (lua_gettop(L) != 3){
		std::cout << "Error: SetSpritePosition function requires 3 arguments." << '\n';
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
    
    // Dereference the sprite and check them for collision
    Sprite& ref1 = *(Sprite*)lua_touserdata(L, 1);
	ref1.x = luaL_checknumber(L,2);
	ref1.y = luaL_checknumber(L,3);
	
    return 0;
}

// Function DrawSprite draws a sprite's texture
int DrawSprite(lua_State* L){
	// If we're passed a table, get CData
	if (lua_istable(L, 1)) {
        lua_getfield(L, 1, "CData");
        lua_replace(L, 1);
    }
    
    // If the sprite does not exist pass an error
    if (!lua_touserdata(L, 1)){
        lua_error(L);
    }
    
    // Finally display the sprite's texture
    Sprite& ref = *(Sprite*)lua_touserdata(L, 1);
    if (ref.texture != -1){
		SDL_Rect dstrect = {ref.x, ref.y, ref.w, ref.h};
		SDL_RenderCopy(renderer,textures.at(ref.texture), NULL, &dstrect);
	}
    return 0;
}

// Function CreateTexture creates and returns a texture from a filepath
int CreateTexture(lua_State* L){
	// Check for correct number of arguments
	if (lua_gettop(L) != 1){
		std::cout << "Error: CreateTexture function requires 1 argument."  << '\n';
	}
	
	// If we're passed a table, get CData
	if (lua_istable(L, 1)) {
        lua_getfield(L, 1, "CData");
        lua_replace(L, 1);
    }
    
    // Finally create the texture
	textures.push_back(SDL_CreateTextureFromSurface(renderer,IMG_Load(luaL_checkstring(L,1))));
	lua_pushnumber(L,textures.size() - 1);
	
	// Check for errors
	if (!textures.at(textures.size() - 1)){
		lua_Debug info;
		lua_getstack(L,1, &info);
    	lua_getinfo(L, "l", &info);
		std::cout << "Error: could not load texture file on line " << info.currentline << std::endl;
	}
	  
    return 1;
}

// Function CreateSprite creates and returns a sprite object
int CreateSprite(lua_State* L){
	// Check for correct number of arguments
	int argc = lua_gettop(L);
	if (argc != 5 && argc != 4){
		std::cout << "Error: CreateSprite function requires 4 or 5 arguments."  << '\n';
	}
	
	// Create the sprite
	try{

	if (argc == 5){
		new (lua_newuserdata(L,sizeof(Sprite))) Sprite(luaL_checkinteger(L,1),luaL_checkinteger(L,2),
		luaL_checkinteger(L,3),luaL_checkinteger(L,4),luaL_checkinteger(L,5));
	}else if (argc == 4){
		new (lua_newuserdata(L,sizeof(Sprite))) Sprite(luaL_checkinteger(L,1),luaL_checkinteger(L,2),
		luaL_checkinteger(L,3),luaL_checkinteger(L,4),-1);		
	}

	}catch(std::exception& e){
		std::cout << e.what();
	}
	
	return 1;
}
