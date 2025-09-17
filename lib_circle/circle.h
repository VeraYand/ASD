#pragma once

#include "../lib_point/point.h"

class Circle {
	Point _centre;
	int _radius;
public:
	Circle();
	Circle(Point centre, int radius);
	Circle(const Circle&);

	Point get_centre() const;
	int get_radius() const;

	void set_radius(int radius);

	bool operator ==(const Circle&) const noexcept;
};
