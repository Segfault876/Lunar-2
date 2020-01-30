#include "global.hpp"

bool Sprite::Collides(Sprite s){
	return x < s.x+s.w && s.x < x+w && y < s.y+s.h && s.y < y+h;
}
Sprite::Sprite(int x,int y,int w,int h,int texture){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->texture = texture;
}
Clock::Clock(){
	currentTime = 0;
	lastTime = 0;
}
Sound::Sound(const char* filelocation,unsigned int channel){
	this->channel = channel;
	sound = Mix_LoadWAV(filelocation);
}
Font::Font(const char* filelocation,int size){
	font=TTF_OpenFont(filelocation, size);
}
Text::Text(int texture){
	this->texture = texture;
}
