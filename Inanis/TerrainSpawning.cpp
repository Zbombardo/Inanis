#include "TerrainSpawning.h"
#include <iostream>

TerrainSpawning::TerrainSpawning(SDL_Renderer* _Renderer) {
	
	if (!init(_Renderer)) {
		std::cerr << "Terrain Spawner could not initialize\n";
	}
	
	b_halt = 0;		//by default image should not be halted at the beginning
}

bool TerrainSpawning::init(SDL_Renderer* _Renderer) {
	
	this->_Renderer = _Renderer;				//I liked it more when objects _Renderer could have nullptr as value
	if (this->_Renderer == nullptr) {
		std::cerr << "Could not initialize terrain renderer\n" << SDL_GetError();
		b_ButtonClosed = 1;
		return 0;
	}

	b_ButtonClosed = 0;
	_Surface = IMG_Load(IMG_PATH);
	if (_Surface == nullptr) {
		std::cerr << "Could not initalize texture\n" << SDL_GetError();
		return 0;
	}
	_Texture = SDL_CreateTextureFromSurface(_Renderer, _Surface);
	if (_Texture == nullptr) {
		std::cerr << "Could not initialize texture";
		return 0;
	}

	srand(time(NULL));			//seeds rand with current time
	return 1;
}

bool TerrainSpawning::spawn() {
	
	//=====================THIS IS FOR AFTER MVP=============================
	/*int length = rand() % (dimensions::maxPlatformLength - dimensions::minPlatformLength) + dimensions::minPlatformLength;
	newPlatform.h = dimensions::platformHeight;
	newPlatform.w = length;
	newPlatform.x = dimensions::terrainSpawnerX;*/

	std::cerr << generatingOrder.size() << std::endl;

	//the key thing in this if is condition order (short circuit)
	//isColliding() must NOT be called with the empty platforms cause it will throw exception
	if (platforms.size() != 0 && isColliding() || generatingOrder.size() == 0)	//if there are elements and there is "spawning collision" OR there are no more Platforms to add
		return 0;																//DO NOT add new Platform

#if 0		//this one is longer and slower but easeier to understand so I left it here
	SDL_Rect newRect;
	newRect.x = dimensions::terrainSpawnerX;	//all rectangles have the same starting X coordinate
	newRect.h = dimensions::platformHeight;
	newRect.w = dimensions::maxPlatformLength;

	TerrainPosition pos = generatingOrder.front();	//gets next TerrainPosition to be generated
	switch (pos)									//and sets Y coordinate accordingly
	{
	case TerrainPosition::LOWER:
		newRect.y = dimensions::terrainLowerSpawnerY;
		break;
	case TerrainPosition::MIDDLE:
		newRect.y = dimensions::terrainMiddleSpawnerY;
		break;
	case TerrainPosition::UPPER:
		newRect.y = dimensions::terrainUpperSpawnerY;
		break;
	}

	platforms.push_back( Platform(newRect, pos) );	//adds new Platform to the end of the rect

#else	//faster but less readable version, look at the Platform constructor for more info
	platforms.push_back( Platform(dimensions::terrainSpawnerX, dimensions::maxPlatformLength, dimensions::platformHeight, generatingOrder.front()) );
#endif
	generatingOrder.pop();	//remove this generated pos
	
	return 1;
}

bool TerrainSpawning::isColliding() {
	
	if (platforms.back().x + platforms.back().w > dimensions::terrainSpawnerX)	// if the right side of the Platform is right of the spawner
		return 1;																// spawner and last Platform are overlapping

	return 0;
}

void TerrainSpawning::update() {
	
	int newX;								//new value of x coordinate
	int numOFAlreadyPassed(0);				//number of non-colliding platform that have already been passed 

	for (std::deque<Platform>::iterator it = platforms.begin(); it != platforms.end(); ++it) {
		newX = it->x - dimensions::velocity;			//shift to the left
		if (newX <= dimensions::terrainDestroyerX) {	//if newX is on the same position as or left to the terrain destroyer, aka if they touch, destroy this Platform 
			destroy();
			it = platforms.begin() + numOFAlreadyPassed;	//set iterator `it` from beggining and add already passed, because platforms seem like it hasn't " updated" itself
			continue;	//don't update destroyed Platforms x
		}
		++numOFAlreadyPassed;	//increase number of non-colliding platforms
		it->x = newX;			//set Platforms x to its new value
	}
	if (generatingOrder.size() == 0 && (platforms.back().x + dimensions::maxPlatformLength) <= dimensions::resolution[0])	//if there are no more Platforms to add
		b_halt = 1;																		//AND  last Platform has fully entered the screen halt the screen, freeze it
}

void TerrainSpawning::draw() {

   /*=======TO DO AFTER MVP=========
	 replace NULL with Rect of the same dimensions as current Platform, `it`
	 SDL_Rect crop;*/

	for (std::deque<Platform>::iterator it = platforms.begin(); it != platforms.end(); ++it) {	//iterate through all living Platforms and give them to the _Renderer
		SDL_RenderCopy(_Renderer, _Texture, NULL, &*it);
	}
}

void TerrainSpawning::generateMap(int numOfPlatforms) {
	
	//implicitly LOWER = 0, MIDDLE = 1, UPPER = 2
	int pos;
	generatingOrder.push(TerrainPosition::LOWER);		//by default start at lower
	for (int i(0); i < numOfPlatforms; i++) {
		if (generatingOrder.back() == TerrainPosition::LOWER) {		//if last generated is LOWER then next one can be either LOWER or MIDDLE
			pos = rand() % 2;	//get either 0 or 1, aka LOWER or MIDDLE
		}
		else {
			pos = rand() % 3;	//get any TerrainPosition
		}
		generatingOrder.push(static_cast<TerrainPosition>(pos)); //static_cast TerrainPosition enum to int
	}
}

const Platform* TerrainSpawning::firstPlatform(TerrainPosition pos) {

	for (std::deque<Platform>::iterator it = platforms.begin(); it != platforms.end(); ++it) {	//iterate through all living Platforms
		if ((*it).getPosition() == pos) return &*it;	//until there is one that matches our wanted TerrainPosition
	}
	return nullptr;	//if there is none, return nullptr
}