#pragma once

#include "Defs.h"

class Player {
public:
	Player(xyz location, xyz velocity, float angle, int sector);
	~Player();

	void move(float dx, float dy);
	void update();
	int getSector();

	float getX();
	float getY();
	float getZ();

	float getAngle();
	float getSin();
	float getCos();

	void setAngle(float angle);

private: 
	xyz _location;
	xyz _velocity;

	float _angle, _anglesin, _anglecos, _yaw;
	int _sector;
};