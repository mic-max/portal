#pragma once

#include <algorithm>

// Data Structures

struct xy {
	float x, y;
};

struct xyz {
	float x, y, z;
};

struct item {
	int sectorNum, startx, endx;
};

// Math Functions
/*
float clamp(float x, float low, float high) {
	return std::min(std::max(x, low), high);
}

float vxs(float x0, float y0, float x1, float y1) {
	return x0 * y1 - x1 * y0;
}

bool overlap(float a0, float a1, float b0, float b1) {
	return std::min(a0, a1) <= std::max(b0, b1) && std::min(b0, b1) <= std::max(a0, a1);
}

bool intersectBox(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
	return overlap(x0, x1, x2, x3) && overlap(y0, y1, y2, y3);
}

float pointSide(float px, float py, float x0, float y0, float x1, float y1) {
	return vxs(x1 - x0, y1 - y0, px - x0, py - y0);
}

xy intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	return {
		vxs(vxs(x1, y1, x2, y2), (x1) -(x2), vxs(x3, y3, x4, y4), (x3) -(x4)) / vxs((x1) -(x2), (y1) -(y2), (x3) -(x4), (y3) -(y4)),
		vxs(vxs(x1, y1, x2, y2), (y1) -(y2), vxs(x3, y3, x4, y4), (y3) -(y4)) / vxs((x1) -(x2), (y1) -(y2), (x3) -(x4), (y3) -(y4))
	};
}
*/