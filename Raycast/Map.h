#pragma once

// #include "Game.h" // temp for sdl rect
#include "MapSector.h"
#include "Player.h"
#include <vector>

class Map {
public:
	Map();
	~Map();

	void loadMap(const char* map);
	void drawMap(int width, int height);

private:
	void verticalLine(int x, int y1, int y2, int top, int mid, int bot);
	// SDL_Rect src, dest;

	std::vector<MapSector*> _sectors;
	Player* _player;
};