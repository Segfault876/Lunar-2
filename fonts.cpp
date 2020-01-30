#include "global.hpp"
#include "methods.hpp"

SDL_Event event;
SDL_Window * window;
SDL_Renderer * renderer;
unsigned int channel;
std::vector<SDL_Texture *> textures;

// Function CreateFont creates and returns a sprite object
int CreateFont(lua_State* L){
	// Check for correct number of arguments
	int argc = lua_gettop(L);
	if (argc != 2 && argc != 1){
		std::cout << "Error: CreateFont function requires 2 or 1 arguments."  << '\n';
	}
	
	// Create the font
	if (argc == 2){
		new (lua_newuserdata(L,sizeof(Font))) Font(luaL_checkstring(L,1),luaL_checkinteger(L,2));
	}else if (argc == 1){
		new (lua_newuserdata(L,sizeof(Font))) Font(luaL_checkstring(L,1),12);		
	}
	
	return 1;
}
int CreateText(lua_State* L){
	// Check for correct number of arguments
	int argc = lua_gettop(L);
	if (argc != 2 && argc != 5){
		std::cout << "Error: CreateText function requires 2 or 5 arguments."  << '\n';
	}
	
	// If we're passed a table, get CData
	if (lua_istable(L, 2)) {
        lua_getfield(L, 2, "CData");
        lua_replace(L, 2);
    }
    
    // If the font does not exist pass an error
    if (!lua_touserdata(L, 2)){
        lua_error(L);
    }
    
    // Finally display the sprite's texture
    Font& ref = *(Font*)lua_touserdata(L, 2);
	
	// Create the text
	if (argc == 5){
		SDL_Color color = {luaL_checkinteger(L,3),luaL_checkinteger(L,4),luaL_checkinteger(L,5)};
		textures.push_back(
		SDL_CreateTextureFromSurface(renderer,TTF_RenderText_Solid(ref.font,luaL_checkstring(L,1),color)));
		new (lua_newuserdata(L,sizeof(Text))) Text(textures.size()-1);
	}else if (argc == 2){
		SDL_Color color = {0,0,0};
		textures.push_back(
		SDL_CreateTextureFromSurface(renderer,TTF_RenderText_Solid(ref.font,luaL_checkstring(L,1), color)));
		new (lua_newuserdata(L,sizeof(Text))) Text(textures.size()-1);
	}	
	
	return 1;
}

// Function DrawSprite draws a sprite's texture
int DrawText(lua_State* L){
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
    int texW;
    int texH;
    Text& ref = *(Text*)lua_touserdata(L,1);
    SDL_QueryTexture(textures.at(ref.texture), NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {luaL_checkinteger(L,2), luaL_checkinteger(L,3),texW,texH};
	SDL_RenderCopy(renderer,textures.at(ref.texture), NULL, &dstrect);
    
    return 0;
}
