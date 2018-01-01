#include "Player.h"
#include "MapSector.h"

#include <math.h>

Player::Player(xyz location, xyz velocity, float angle, int sector) {
	_location = location;
	_velocity = velocity;
	_angle = angle;
	_sector = sector;

	// set location.z = sector->getFloor() + eye height
}

Player::~Player() {}

void Player::move(float dx, float dy) {
	float px = _location.x;
	float py = _location.y;

	MapSector* sector = nullptr; // get sector from map using _sector

	// add intersect box with 4 floats and 2 xy's
	for (int i = 0; i < sector->numVertices(); i++) {
		/*
		if (sector->getNeighbour(i) >= 0
		&& intersectBox(px, py, px + dx, py + dy,
			sector->getVertex(i + 0).x, sector->getVertex(i + 0).y, sector->getVertex(i + 1).x, sector->getVertex(i + 1).y)
		&& pointSide(px + dx, py + dy, sector->getVertex(i + 0).x, sector->getVertex(i + 0).y, sector->getVertex(i + 1).x, sector->getVertex(i + 1).y) < 0) {
			_sector = sector->getNeighbour(i);
			break;
		}
		*/
	}

	_location.x += dx;
	_location.y += dy;
	_anglesin = sin(_angle); // does the angle even change?
	_anglecos = cos(_angle);
}

int Player::getSector() {
	return _sector;
}
