#pragma once
#include "../lib_point/point.h"


class Point3D: public Point{
	int _coordZ;
public:
	Point3D();
	Point3D(int x, int y, int z);
	Point3D(const Point3D&);

	int get_z() const;

	bool operator ==(const Point3D&) const noexcept;
};