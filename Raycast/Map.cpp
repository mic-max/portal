#include "Map.h"
#include "Defs.h"
//#include "SDL.h"
#include "Game.h"

#include <sstream>
#include <fstream>
#include <iostream> // for testing
#include <queue>
#include <algorithm>

Map::Map() {
	loadMap("map1.txt");
}

Map::~Map() {}

void Map::loadMap(const char* map) {
	std::vector<xy> vertices;
	xy v;

	// open filepath
	std::ifstream mapFile(map);
	if (!mapFile.is_open()) {
		std::cout << "File Failed : " << map << std::endl;
		return;
	}

	for (std::string line; getline(mapFile, line); ) {
		std::string type;
		std::istringstream in(line);
		in >> type;

		if (!type.compare("vertex")) {
			in >> v.y;

			while (in >> v.x) {
				std::cout << "Vertex: ( " << v.x << ", " << v.y << " )" << std::endl;
				vertices.push_back(v);
			}

		} else if (!type.compare("sector")) {
			std::vector<int> num;
			int vert;
			float floor, ceil;

			in >> floor >> ceil;

			while (in >> vert) {
				num.push_back(vert);
			}

			int m = (int) (num.size() / 2);
			MapSector* sector = new MapSector(floor, ceil, m);

			std::cout << "Sector #" << _sectors.size() << ": ( " << floor << ", " << ceil << " )" << std::endl;
			for (int i = 0; i < m; i++) {
				std::cout << " Vertex #: " << num[i] << ", Neighbour #: " << num[m + i] << std::endl;
				sector->addVertex(vertices[num[i]], num[m + i]);
			}

			_sectors.push_back(sector);
		} else if (!type.compare("player")) {
			int sector;
			float angle;

			in >> v.x >> v.y >> angle >> sector;
			_player = new Player({v.x, v.y, 0}, {0, 0, 0}, angle, sector);
			std::cout << "Player: ( " << v.x << ", " << v.y << " ), Angle: " << angle << ", Sector #: " << sector << std::endl;
		} else {
			std::cout << std::endl;
		}
	}

	mapFile.close();
}

void Map::drawMap(int width, int height) {

	std::queue<item> queue;

	int* ytop = (int*) calloc(width, sizeof(int));
	int* ybot = (int*) calloc(width, sizeof(int));
	int* renderedSectors = (int*) calloc(_sectors.size(), sizeof(int));

	for (int i = 0; i < width; i++)
		ybot[i] = height- 1;

	queue.push({_player->getSector(), 0, width - 1});

	while (!queue.empty()) {
		item now = &queue.back; // front or back?
		queue.pop();

		if (renderedSectors[now.sectorNum] & 0x21)
			continue;

		renderedSectors[now.sectorNum]++;
		MapSector* sect = _sectors[now.sectorNum];

		for (int i = 0; i < sect->numVertices(); i++) {
			// stuff

			int neighbour = sect->getNeighbour(i);

			int x1 = 0;
			int x2 = 45;

			int startx = std::max(x1, now.startx);
			int endx = std::min(x2, now.endx);

			for (int x = startx; i <= endx; i++) {

				int cya = 115;
				int cyb = 300;
				verticalLine(x, ytop[x], cya - 1, 0x111111, 0x222222, 0x111111);
				verticalLine(x, cyb + 1, ybot[x], 0x0000ff, 0x0000aa, 0x0000ff);

				if (neighbour >= 0) {
					//verticalLine(x, );
					//verticalLine(x, );
				} else {
					//verticalLine(x, );
				}
			}

			if (neighbour >= 0 && endx >= startx && true) { // some queue thing
				queue.push({neighbour, startx, endx});
			}
		}

		renderedSectors[now.sectorNum]++;
	}

	for (int i = 0; i < 800; i++) {
		int rand1 = 0 + (rand() % static_cast<int>(320 - 0 + 1));
		int rand2 = 320 + (rand() % static_cast<int>(640 - 320 + 1));

		verticalLine(i, rand1, rand2, 0, 0, 0);
	}



}

void rgbChannels(int rgb, int& r, int& g, int& b) {
	r = (rgb >> 16) & 0xff;
	g = (rgb >> 8) & 0xff;
	b = rgb & 0xff;
}

void Map::verticalLine(int x, int y1, int y2, int top, int mid, int bot) {
	// clamp y1 and y2 between 0 and screen height (640)
	int r, g, b;

	// TOP
	rgbChannels(top, r, g, b);
	SDL_SetRenderDrawColor(Game::_renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(Game::_renderer, x, y1);
	std::cout << r << " " << g << " " << b << std::endl;

	// MIDDLE
	rgbChannels(mid, r, g, b);
	SDL_SetRenderDrawColor(Game::_renderer, r, g, b, SDL_ALPHA_OPAQUE);	
	SDL_RenderDrawLine(Game::_renderer, x, y1 + 1, x, y2);
	std::cout << r << " " << g << " " << b << std::endl;

	// BOTTOM
	rgbChannels(bot, r, g, b);
	SDL_SetRenderDrawColor(Game::_renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(Game::_renderer, x, y2);
	std::cout << r << " " << g << " " << b << std::endl;

	getchar();
}