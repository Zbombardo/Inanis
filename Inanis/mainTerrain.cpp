#include "TerrainSpawning.h"
#include <iostream>

int main(int argc, char** args) {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Failed to initialise SDL2_EVERYTHING!  SDL Error: " << SDL_GetError() << std::endl;
		return 0;
	}
	else {
		std::cout << "Sucessfully initialised SDL2 " << std::endl;

	}

	if (IMG_Init(IMG_INIT_PNG) < 0) {
		std::cout << "FAILED initialising SDL2_Image! SDL_Error: " << SDL_GetError() << std::endl;
		return 0;
	}
	else {
		std::cout << "Succesfull SDL2_Image init" << std::endl;
	}

	TerrainSpawning TSpawn = TerrainSpawning();
	TSpawn.generateMap();
	int n(0);

	SDL_Surface* _S = IMG_Load(IMG_PATH);
	if (_S == nullptr) {
		std::cerr << "Could not initalize texture\n" << SDL_GetError();
		return 0;
	}
	SDL_Texture* _T = SDL_CreateTextureFromSurface(TSpawn.getRenderer(), _S);
	if (_S == nullptr) {
		std::cerr << "Could not initialize texture";
		return 0;
	}
	SDL_Rect r = { 0, 0, 180, 180 };
	SDL_RenderCopy(TSpawn.getRenderer(), _T, NULL, &r);
	while (TSpawn.getB_ButtonClosed()) {
		if (n % 100 == 0 && !TSpawn.getB_Halt()) {
			n = 0;
			SDL_RenderClear(TSpawn.getRenderer());
			TSpawn.spawn();
			TSpawn.update();
			TSpawn.draw();
			SDL_RenderPresent(TSpawn.getRenderer());
		}
		n++;
	}

	SDL_Quit();
	std::cerr << "Exited like a boss";
	return 0;
}