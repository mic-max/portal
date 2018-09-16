#include "Map.h"
#include "Defs.h"
//#include "SDL.h"
#include "Game.h"

#include <sstream>
#include <fstream>
#include <iostream> // for testing
#include <queue>
#include <algorithm>

float hfov = 0.7 * 640;
float vfov = 30;


Map::Map(Entity* player) {
	loadMap("map1.txt");
	_player = player;
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
				// std::cout << "Vertex: ( " << v.x << ", " << v.y << " )" << std::endl;
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

			// std::cout << "Sector #" << _sectors.size() << ": ( " << floor << ", " << ceil << " )" << std::endl;
			for (int i = 0; i < m; i++) {
				// std::cout << " Vertex #: " << num[i] << ", Neighbour #: " << num[m + i] << std::endl;
				sector->addVertex(vertices[num[i]], num[m + i]);
			}

			_sectors.push_back(sector);
		} else if (!type.compare("player")) {
			int sector;
			float angle;

			in >> v.x >> v.y >> angle >> sector;
			//_player = new Player({v.x, v.y, 0}, {0, 0, 0}, angle, sector);
			_player->addComponent<PositionComponent>(v.x, v.y, angle, sector);
			// std::cout << "Player: ( " << v.x << ", " << v.y << " ), Angle: " << angle << ", Sector #: " << sector << std::endl;
		} else {
			// std::cout << std::endl;
		}
	}

	mapFile.close();
}
// TODO: move to Defs.h
float vxs(float x0, float y0, float x1, float y1) {
	return x0 * y1 - x1 * y0;
}

xy intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	return {
		vxs(vxs(x1, y1, x2, y2), (x1) -(x2), vxs(x3, y3, x4, y4), (x3) -(x4)) / vxs((x1) -(x2), (y1) -(y2), (x3) -(x4), (y3) -(y4)),
		vxs(vxs(x1, y1, x2, y2), (y1) -(y2), vxs(x3, y3, x4, y4), (y3) -(y4)) / vxs((x1) -(x2), (y1) -(y2), (x3) -(x4), (y3) -(y4))
	};
}

void Map::drawMap(int W, int H) {
	//std::queue<item> queue;

	int* ytop = (int*) calloc(W, sizeof(int));
	int* ybot = (int*) calloc(W, sizeof(int));

	for (int i = 0; i < W; i++)
		ybot[i] = H - 1;

	PositionComponent* pos = &_player->getComponent<PositionComponent>();
	item now = {pos->getSector(), 0, W - 1};

	MapSector* sect = _sectors[now.sectorNum];

	for (int s = 0; s < sect->numVertices(); s++) {
		float vx1 = sect->getVertex(s + 0).x - pos->getX();
		float vy1 = sect->getVertex(s + 0).y - pos->getY();

		float vx2 = sect->getVertex((s + 1) % sect->numVertices()).x - pos->getX();
		float vy2 = sect->getVertex((s + 1) % sect->numVertices()).y - pos->getY();

		float pcos = cos(pos->getAngle());
		float psin = sin(pos->getAngle());

		float tx1 = vx1 * psin - vy1 * pcos;
		float tz1 = vx1 * pcos + vy1 * psin;
		float tx2 = vx2 * psin - vy2 * pcos;
		float tz2 = vx2 * pcos + vy2 * psin;

		if (tz1 <= 0 && tz2 <= 0)
			continue;

		if (tz1 <= 0 || tz2 <= 0) {
			float nearz = 1e-4f;
			float farz = 5;
			float nearside = 1e-5f;
			float farside = 20;

			xy i1 = intersect(tx1, tz1, tx2, tz2, -nearside, nearz, -farside, farz);
			xy i2 = intersect(tx1, tz1, tx2, tz2,  nearside, nearz,  farside, farz);

			if (tz1 < nearz) {
				if(i1.y > 0) {
					tx1 = i1.x;
					tz1 = i1.y;
				} else {
					tx1 = i2.x;
					tz1 = i2.y;
				}
			}

			if (tz2 < nearz) {
				if (i1.y > 0) {
					tx2 = i1.x;
					tz2 = i1.y;
				} else {
					tx2 = i2.x;
					tz2 = i2.y;
				}
			}
		}

		float xscale1 = hfov / tz1;
		float yscale1 = vfov / tz1;
		int x1 = W / 2 - (int) (tx1 * xscale1);

		float xscale2 = hfov / tz2;
		float yscale2 = vfov / tz2;
		int x2 = W / 2 - (int) (tx2 * xscale2);

		if (x1 >= x2 || x2 < now.startx || x1 > now.endx)
			continue;

		float yceil = sect->getCeil() - pos->getZ();
		float yfloor = sect->getFloor() - pos->getZ();

		int neighbour = sect->getNeighbour(s);
		float nyceil = 0;
		float nyfloor = 0;

		if (neighbour >= 0) {
			nyceil = _sectors[neighbour]->getCeil() - pos->getZ();
			nyfloor = _sectors[neighbour]->getFloor() - pos->getZ();
		}

		int y1a = H / 2 - (int) (yceil * yscale1);
		int y1b = H / 2 - (int) (yfloor * yscale1);
		int y2a = H / 2 - (int) (yceil * yscale2);
		int y2b = H / 2 - (int) (yfloor * yscale2);

		int ny1a = H / 2 - (int) (nyceil * yscale1);
		int ny1b = H / 2 - (int) (nyfloor * yscale1);
		int ny2a = H / 2 - (int) (nyceil * yscale2);
		int ny2b = H / 2 - (int) (nyfloor * yscale2);

		int startx = std::max(x1, now.startx);
		int endx = std::min(x2, now.endx);

		for (int x = startx; x <= endx; x++) {
			int ya = (x - x1) * (y2a - y1a) / (x2 - x1) + y1a;
			int cya = clamp(ya, ytop[x], ybot[x]);
			int yb = (x - x1) * (y2b - y1b) / (x2 - x1) + y1b;
			int cyb = clamp(yb, ytop[x], ybot[x]);

			verticalLine(x, ytop[x], cya - 1, 0x111111, 0x222222, 0x111111); // dark grey
			verticalLine(x, cyb + 1, ybot[x], 0x0000FF, 0x0000AA, 0x0000FF); // blue

			if (neighbour >= 0) {
				int nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) + ny1a;
				int cnya = clamp(nya, ytop[x], ybot[x]);
				int nyb = (x - x1) * (ny2b - ny1b) / (x2 - x1) + ny1b;
				int cnyb = clamp(nyb, ytop[x], ybot[x]);

				verticalLine(x, cya, cnya - 1, 0, x == x1 || x == x2 ? 0 : 0xAAAAAA, 0); // black or light grey
				ytop[x] = clamp(std::max(cya, cnya), ytop[x], H - 1);

				verticalLine(x, cnyb + 1, cyb, 0, x == x1 || x == x2 ? 0 : 0x7C00D9, 0); // pink
				ybot[x] = clamp(std::min(cyb, cnyb), 0, ybot[x]);

				verticalLine(x, ytop[x], ybot[x], 0x00AA00, 0x00AA00, 0xAA0000); // green
			} else {
				verticalLine(x, cya, cyb, 0, x == x1 || x == x2 ? 0 : 0xAAAAAA, 0); // black or light grey
			}
		}
	}

	delete ytop;
	delete ybot;
}

void Map::update() {
	_player->update();
	PositionComponent* pos = &_player->getComponent<PositionComponent>();
	std::cout << pos->getX() << ", " << pos->getY() << std::endl;
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

	// MIDDLE
	rgbChannels(mid, r, g, b);
	SDL_SetRenderDrawColor(Game::_renderer, r, g, b, SDL_ALPHA_OPAQUE);	
	SDL_RenderDrawLine(Game::_renderer, x, y1 + 1, x, y2);

	// BOTTOM
	rgbChannels(bot, r, g, b);
	SDL_SetRenderDrawColor(Game::_renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(Game::_renderer, x, y2);
}