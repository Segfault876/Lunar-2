extern "C"{
    #include "lua/lua.h"
    #include "lua/lauxlib.h"
    #include "lua/lualib.h"
}
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

class Sprite{ 
public:
	int x,y,w,h,texture;
	bool Collides(Sprite s);
	Sprite(int x,int y,int w,int h,int texture);
};
class Clock{
public:
	unsigned int lastTime;
	unsigned int currentTime;
	unsigned int channel;
	Clock();
};
class Sound{
public:
	Mix_Chunk *sound;
	bool isPlaying;
	unsigned int channel;
	Sound(const char * filelocation,unsigned int channel);
};
class Font{
public:
	TTF_Font *font;
	Font(const char* filelocation,int size);
};
class Text{
public:
	int texture;
	Text(int texture);
};
