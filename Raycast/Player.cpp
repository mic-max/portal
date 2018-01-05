#include "Player.h"
#include "MapSector.h"

#include <math.h>

Player::Player(xyz location, xyz velocity, float angle, int sector) {
	_location = location;
	_velocity = velocity;

	_angle = angle;
	_anglesin = sin(angle);
	_anglecos = cos(angle);

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

void Player::update() {
	//setAngle(_angle);
	_location.x -= 0.1f;
}

int Player::getSector() {
	return _sector;
}

float Player::getX() {
	return _location.x;
}

float Player::getY() {
	return _location.y;
}

float Player::getZ() {
	return _location.z;
}

float Player::getAngle() {
	return _angle;
}

float Player::getSin() {
	return _anglesin;
}

float Player::getCos() {
	return _anglecos;
}

void Player::setAngle(float angle) {
	_angle = angle;
	_anglesin = sin(angle);
	_anglecos = cos(angle);
}
