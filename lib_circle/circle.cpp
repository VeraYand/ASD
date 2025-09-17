#include "circle.h"
#include <stdexcept>

Circle::Circle() : _centre(0, 0), _radius(1) {}
Circle::Circle(Point centre, int radius) :_centre(centre) {
	set_radius(radius);
}
Circle::Circle(const Circle& other) : _centre(other._centre), _radius(other._radius) {}

Point Circle::get_centre() const {
	return _centre;
}
int Circle::get_radius() const {
	return _radius;
}

void Circle::set_radius(int radius) {
	if (radius <= 0) {
		throw std::invalid_argument("Input Error: the radius must be positive!");
	}
	_radius = radius;
}

bool Circle::operator ==(const Circle& other) const noexcept {
	return (_centre == other.get_centre() && _radius == other.get_radius());
}