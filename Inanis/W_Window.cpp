#include "W_Window.h"

bool W_Window::windowSetup(){

	_Window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, 0);	//windowed by default
	if (_Window == nullptr) {
		std::cerr << "Could not initialize window \"\n" << title << "\".";
		std::cerr << SDL_GetError();
		return 0;
	}

	b_closed = 0;

	_Renderer = SDL_CreateRenderer(_Window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (_Renderer == nullptr) {
		std::cerr << "Could not initialize window \"" << title << "\"'s renderer\n";
		std::cerr << SDL_GetError();
		return 0;
	}

	return 1;
}

W_Window::W_Window(const std::string title, int width, int height, int xpos, int ypos) :
					title(title), width(width), height(height), xpos(xpos), ypos(ypos)
{

	if (!windowSetup()) {
		b_closed = 1;
	}

	std::cout << "Succesfully constructed window: " << title << "\n";
}