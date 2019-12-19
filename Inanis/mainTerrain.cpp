#include "TerrainSpawning.h"
#include <iostream>

#define LVL_SIZE 112	//change lvl size, num of platforms
bool init(SDL_Window* Win, SDL_Renderer* Rect);

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

#if 1
	SDL_Window* _Win = SDL_CreateWindow("Neko smece",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		dimensions::resolution[0],
		dimensions::resolution[1], 0);
	if (_Win == nullptr) {
		std::cerr << "Could not initialize TerrainWindow\n" << SDL_GetError();
		return EXIT_FAILURE;
	}

	SDL_Renderer* _Rend = SDL_CreateRenderer(_Win, -1, SDL_RENDERER_PRESENTVSYNC);
	if (_Rend == nullptr) {
		std::cerr << "Could not initialize terrain renderer\n" << SDL_GetError();
		return EXIT_FAILURE;
	}
	
#else
	SDL_Window* _Win = nullptr;
	SDL_Renderer* _Rend = nullptr;

	if (!init(_Win, _Rend)) {
		return EXIT_FAILURE;
	}
#endif

	TerrainSpawning TSpawn = TerrainSpawning(_Rend);
	TSpawn.generateMap(LVL_SIZE);
	int n(0);

	SDL_Event Event;
	while (!TSpawn.getB_ButtonClosed()) {
		if (SDL_PollEvent(&Event) && Event.type == SDL_QUIT) break;
		if (n % 2 == 0 && !TSpawn.getB_Halt()) {
			SDL_RenderClear(_Rend);
			TSpawn.spawn();
			TSpawn.update();
			TSpawn.draw();
			SDL_RenderPresent(_Rend);
		}
		n++;
	}

	SDL_Quit();
	std::cerr << "Exited like a boss";
	return 0;
}

bool init(SDL_Window* _Window, SDL_Renderer* _Renderer) {

	_Window = SDL_CreateWindow("Neko smece",
							   SDL_WINDOWPOS_UNDEFINED,
							   SDL_WINDOWPOS_UNDEFINED,
							   dimensions::resolution[0],
					           dimensions::resolution[1], 0);
	if (_Window == nullptr) {
		std::cerr << "Could not initialize TerrainWindow\n" << SDL_GetError();
		return 0;
	}

	_Renderer = SDL_CreateRenderer(_Window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (_Renderer == nullptr) {
		std::cerr << "Could not initialize terrain renderer\n" << SDL_GetError();
		return 0;
	}

	return 1;
}