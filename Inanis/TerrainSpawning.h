#pragma once
#include "dimensions.h"
#include "SpawnerPosition.h"
#include <SDL_image.h>
#include <SDL.h>
#include <vector>
#include <time.h>

#define IMG_PATH "platform.png"
#define MAP_SIZE 20

class TerrainSpawning
{
private:
	
	SDL_Rect upperSpawnerArray[dimensions::maxNumOfPlatform];
	SDL_Rect middleSpawnerArray[dimensions::maxNumOfPlatform];
	SDL_Rect lowerSpawnerArray[dimensions::maxNumOfPlatform];
	
	SDL_Renderer* _Renderer;
	SDL_Window* _Window;
	SDL_Texture* _Texture;
	SDL_Surface* _Surface;

	int numOfUpper;
	int numOfMiddle;
	int numOfLower;
	
	bool b_halt;
	bool b_ButtonClosed;

	std::vector<SDL_Rect> platforms;
	std::vector<SpawnerPosition> generatingOrder;				//order in which platforms will be spawned

private:
	bool isColliding();
	bool init();
	SDL_Rect firstLowest();
	SDL_Rect firstMiddle();
	SDL_Rect firstUpper();
public:
	TerrainSpawning();
	void generateMap();
	bool spawn();
	void update();
	void destroy();
	void draw();	
	SDL_Rect firstPlatform(SpawnerPosition pos);
	SDL_Renderer* getRenderer() { return _Renderer; }
	bool getB_Halt() { return b_halt; }
	bool getB_ButtonClosed() { return b_ButtonClosed; }
};

