main:
	g++ -o main main.cpp objects.cpp sound.cpp graphics.cpp fonts.cpp input.cpp system.cpp time.cpp -llua5.3 -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image
