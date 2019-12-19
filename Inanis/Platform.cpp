#include "Platform.h"

Platform::Platform(int x, int w, int h, TerrainPosition pos) : SDL_Rect{x, -1, w, h}, pos(pos) {	//this->y is -1 (somedumb value) but this creation is faster
	
	switch (pos)	//depending on TerrainPosition we are assigning y coordinate accordingly
	{
	case TerrainPosition::LOWER:
		this->y = dimensions::terrainLowerSpawnerY;
		break;
	case TerrainPosition::MIDDLE:
		this->y = dimensions::terrainMiddleSpawnerY;
		break;
	case TerrainPosition::UPPER:
		this->y = dimensions::terrainUpperSpawnerY;
		break;
	}
}