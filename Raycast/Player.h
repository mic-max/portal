#pragma once

#include "Defs.h"

class Player {
public:
	Player(xyz location, xyz velocity, float angle, int sector);
	~Player();

	void move(float dx, float dy);
	int getSector();

private: 
	xyz _location;
	xyz _velocity;

	float _angle, _anglesin, _anglecos, _yaw;
	int _sector;
};