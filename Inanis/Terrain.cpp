/*#include <iostream>
#include <SDL.h>

#include "W_Window.h"

bool SDLSetup();

int main(int argc, char** args) {


	if (!SDLSetup()) {
		return 0;
	}

	constexpr int resolution[] = { 1366, 768 };	//screen resolution
	W_Window MainFrame("Inanis", resolution[0], resolution[1], 50, 50);

	SDL_Event event;
	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			std::cout << "Quit SDL.\n";
			break;
		}
	}

	SDL_Quit();

	return 0;
}

bool SDLSetup() {


	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Failed to initialise SDL2_EVERYTHING!  SDL Error: " << SDL_GetError() << std::endl;
		return 0;
	}
	else {
		std::cout << "Sucessfully initialised SDL2 " << std::endl;

	}

	return 1;
}*/