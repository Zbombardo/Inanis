#include "Platform.h"

Platform::Platform(int x, int w, int h, TerrainPosition pos) : SDL_Rect{x, -1, w, h}, pos(pos) {
	
	switch (pos)
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