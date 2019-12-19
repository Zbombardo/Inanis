#pragma once
#include "dimensions.h"
#include "TerrainPosition.h"
#include "Platform.h"
#include <SDL_image.h>
#include <SDL.h>
#include <deque>
#include <queue>
#include <time.h>

#define IMG_PATH "platform.png"								//path to platform.png
#define MAP_SIZE 20											//number of platforms in this level

class TerrainSpawning
{
private:
	SDL_Renderer* _Renderer;
	SDL_Texture* _Texture;
	SDL_Surface* _Surface;
	
	bool b_halt;											//if all needed platforms have been generated and are on screen, movement should be halted
	bool b_ButtonClosed;									//closes window in my main, could be unnecessary for Nocthonax

	std::deque<Platform> platforms;							//all current living platforms
	std::queue<TerrainPosition> generatingOrder;			//order in which platforms will be spawned

private:
	bool isColliding();										//tests wether there is spawning collision
	bool init(SDL_Renderer* _Renderer);
	
public:
	TerrainSpawning(SDL_Renderer* _Renderer);				//argument is global renderer
	void generateMap() { generateMap(MAP_SIZE); }			//generates spawning order of this map, should be called right after object creation; 
															//potentially could be added in constructor
	void generateMap(int numberOfPlatforms);				//argument passed is number of platforms to be added
	void generateMap(long long lengthOfMap);				//======TO BE IMPLEMENTED AFTER MVP======, pixel length of a map

	bool spawn();											//spawns new platform if possible
	void update();											//updates Platforms map position and destroys them if necessary
	void destroy() { platforms.pop_front(); }				//destroys platform
	void draw();											//gives drawing content to _Renderer for each PLatform
	
	const Platform* firstPlatform(TerrainPosition pos);		//gives pointer to first Platform at TerrainPosition
	const Platform* firstLowest() { return firstPlatform(LOWER); }
	const Platform* firstMiddle() { return firstPlatform(MIDDLE); }
	const Platform* firstUpper() { return firstPlatform(UPPER); }

	SDL_Renderer* getRenderer() { return _Renderer; }
	bool getB_Halt() { return b_halt; }
	bool getB_ButtonClosed() { return b_ButtonClosed; }
};

