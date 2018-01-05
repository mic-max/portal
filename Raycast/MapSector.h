#pragma once

#include "Defs.h"
#include <vector>

class MapSector {
public:
	MapSector(float floor, float ceil, int npoints);
	~MapSector();

	void addVertex(xy vertex, int neighbour);
	int numVertices();

	xy getVertex(int index);
	int getNeighbour(int index);

	float getFloor();
	float getCeil();

private:
	float _floor, _ceil;
	std::vector<xy> _vertices;
	std::vector<int> _neighbours; // if the edge has a neighbouring sector, store it
};