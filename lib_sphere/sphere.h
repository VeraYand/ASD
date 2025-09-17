#pragma once

#include "../lib_circle/circle.h"
#include "../lib_point3d/point3d.h"

class Sphere: public Circle {
	Point3D _centre;
public:
	Sphere();
	Sphere(Point3D centre, int radius);
	Sphere(const Sphere&);

	Point3D get_centre() const;

	bool operator ==(const Sphere&) const noexcept;
};