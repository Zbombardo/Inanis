#include "TerrainSpawning.h"
#include <iostream>

TerrainSpawning::TerrainSpawning() {
	
	if (!init()) {
		std::cerr << "Terrain Spawner could not initialize";
	}
	
	b_halt = 0;
}

bool TerrainSpawning::init() {

	_Window = SDL_CreateWindow("Neko smece",
							   SDL_WINDOWPOS_UNDEFINED,
							   SDL_WINDOWPOS_UNDEFINED,
							   dimensions::resolution[0],
					           dimensions::resolution[1], 0);
	if (_Window == nullptr) {
		std::cerr << "Could not initialize TerrainWindow\n" << SDL_GetError();
		b_ButtonClosed = 0;
		return 0;
	}
	b_ButtonClosed = 1;
	_Renderer = SDL_CreateRenderer(_Window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (_Renderer == nullptr) {
		std::cerr << "Could not initialize terrain renderer\n" << SDL_GetError();
		return 0;
	}

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

	srand(time(NULL));
	return 1;
}

bool TerrainSpawning::spawn() {

	//int length = rand() % (dimensions::maxPlatformLength - dimensions::minPlatformLength) + dimensions::minPlatformLength;
	//newPlatform.h = dimensions::platformHeight;
	//newPlatform.w = length;
	//newPlatform.x = dimensions::terrainSpawnerX;
	
	SDL_Rect newPlatform;
	newPlatform.x = dimensions::terrainSpawnerX;
	newPlatform.h = dimensions::platformHeight;
	newPlatform.w = dimensions::maxPlatformLength;

	std::cerr << generatingOrder.size() << std::endl;
	if (platforms.size() == 0) {
		//std::cerr << "Stavlja prvi\n";
	}
	else if (platforms.size() != 0 && isColliding()) { 
		//std::cerr << "Sudar\n";
		return 0; 
	}
	else if (generatingOrder.size() == 0) {
		return 0;
	}

	//std::cerr << "ide\n";

	switch (generatingOrder.front())
	{
	case SpawnerPosition::LOWER:
		newPlatform.y = dimensions::terrainLowerSpawnerY;
		break;
	case SpawnerPosition::MIDDLE:
		newPlatform.y = dimensions::terrainMiddleSpawnerY;
		break;
	case SpawnerPosition::UPPER:
		newPlatform.y = dimensions::terrainUpperSpawnerY;
		break;
	}

	generatingOrder.erase(generatingOrder.begin());	//remove this generated pos
	
	platforms.push_back(newPlatform);

	return 1;
}

bool TerrainSpawning::isColliding() {
	
	if (platforms.back().x + platforms.back().w > dimensions::terrainSpawnerX)
		return 1;

	return 0;
}

void TerrainSpawning::update() {
	
	int newX;								//new value of x coordinate
	int numOFAlreadyPassed(0);				//number of non-colliding platform that have already been passed 

	for (std::vector<SDL_Rect>::iterator it = platforms.begin(); it != platforms.end(); ++it) {
		newX = it->x - dimensions::velocity;	//shift left
		if (newX <= dimensions::terrainDestroyerX) {
			destroy();
			it = platforms.begin() + numOFAlreadyPassed;	//set iterator it from beggining and add already passed, because platforms seem like it hasn't " updated" itself
			continue;
		}
		numOFAlreadyPassed++;
		it->x = newX;
	}
	if (generatingOrder.size() == 0 && (platforms.back().x + dimensions::maxPlatformLength)<= dimensions::resolution[0])
		b_halt = 1;
}

void TerrainSpawning::draw() {

	for (std::vector<SDL_Rect>::iterator it = platforms.begin(); it != platforms.end(); ++it) {
		SDL_RenderCopy(_Renderer, _Texture, NULL, &*it);
		//SDL_RenderDrawRect(_Renderer, &*it);
	}
}

void TerrainSpawning::destroy() {

	platforms.erase(platforms.begin());
}

void TerrainSpawning::generateMap() {
	
	//implicitly LOWER = 0, MIDDLE = 1, UPPER = 2
	int pos;
	generatingOrder.push_back(SpawnerPosition::LOWER);		//by default start at lower
	for (int i(0); i < MAP_SIZE; i++) {
		if (generatingOrder.back() == SpawnerPosition::LOWER) {		//if last generated is LOWER then next one can be either LOWER or MIDDLE
			pos = rand() % 2;
		}
		else {
			pos = rand() % 3;
		}
		generatingOrder.push_back(static_cast<SpawnerPosition>(pos));
	}
}

SDL_Rect TerrainSpawning::firstLowest() {

	for (std::vector<SDL_Rect>::iterator it = platforms.begin; it != platforms.end(); ++it) {

	}
}