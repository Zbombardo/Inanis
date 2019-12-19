#pragma once
#include <SDL.h>
#include "TerrainPosition.h"
#include "dimensions.h"

class Platform : public SDL_Rect
{
private:
	TerrainPosition pos;

public:
	Platform(SDL_Rect rect, TerrainPosition pos) : SDL_Rect(rect), pos(pos) {}
	Platform(int x, int y, int w, int h, TerrainPosition pos) : SDL_Rect{ x, y, w, h }, pos(pos) {}
	Platform(int x, int w, int h, TerrainPosition pos);
	Platform();
	TerrainPosition getPosition() { return pos; }
};

