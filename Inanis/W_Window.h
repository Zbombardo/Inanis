#pragma once


#include <iostream>
#include <SDL.h>

class W_Window {

private:
	SDL_Window* _Window;
	SDL_Renderer* _Renderer;

	int width, height, xpos, ypos;

	const std::string title;
	bool b_closed;

private:
	bool windowSetup();

public:
	W_Window(const std::string title, int width, int height, int xpos, int ypos);

	SDL_Window* getWindow() { return _Window; }
	SDL_Renderer* getRenderer() { return _Renderer; }

	std::string getTitle() { return title; }
	void setB_Closed(bool state) { b_closed = state; }
	bool getB_Closed() { return b_closed; }

	void draw() { SDL_RenderPresent(_Renderer); }	//update the screen with the rendering performed

};