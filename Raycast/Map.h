#pragma once

// #include "Game.h" // temp for sdl rect
#include "MapSector.h"
#include <vector>
#include "ECS\Components.h"

class Map {
public:
	Map(Entity* player);
	~Map();

	void loadMap(const char* map);
	void drawMap(int width, int height);
	void update();

private:
	void verticalLine(int x, int y1, int y2, int top, int mid, int bot);
	// SDL_Rect src, dest;

	std::vector<MapSector*> _sectors;
	Entity* _player;
};