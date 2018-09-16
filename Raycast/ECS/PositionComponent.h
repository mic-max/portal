#pragma once

#include "Components.h"

class PositionComponent : public Component {
private:
	int _sector;
	float _x, _y, _z; // Vector2D location
	float _angle;

public:
	
	PositionComponent() {
		_x = 0;
		_y = 0;
		_z = 0;
		_angle = 0;
		_sector = 0;
	}

	PositionComponent(float x, float y, float angle, int sector) {
		_x = x;
		_y = y;
		_z = 0;
		_angle = angle;
		_sector = sector;
	}

	int getSector() { return _sector; }
	float getX() { return _x; }
	float getY() { return _y; }
	float getZ() { return _z; }
	float getAngle() { return _angle; }

	void init() override {
		_x = 0;
		_y = 0;
		_z = 0;
		_angle = 0;
		_sector = 0;
	}

	void update() override {
		_x += 0.1f;
		_y += 0.1f;
		_z += 0.1f;
	}

	void setPos(float x, float y, float z) {
		_x = x;
		_y = y;
		_z = z;
	}

	void setSector(int sector) {
		_sector = sector;
	}
};