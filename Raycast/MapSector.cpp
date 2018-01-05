#include "MapSector.h"

MapSector::MapSector(float floor, float ceil, int npoints) {
	_floor = floor;
	_ceil = ceil;
	_vertices.reserve(npoints); // + 1 to make it circular?
	_neighbours.reserve(npoints);
}

MapSector::~MapSector() {}

void MapSector::addVertex(xy vertex, int neighbour) {
	_vertices.push_back(vertex);
	_neighbours.push_back(neighbour);
}

int MapSector::numVertices() {
	return (int) _vertices.size();
}

xy MapSector::getVertex(int index) {
	return _vertices[index];
}

int MapSector::getNeighbour(int index) {
	return _neighbours[index];
}

float MapSector::getFloor() {
	return _floor;
}

float MapSector::getCeil() {
	return _ceil;
}
