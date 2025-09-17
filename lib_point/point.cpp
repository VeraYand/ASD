#include "point.h"

Point::Point() : _coordX(0), _coordY(0) {}
Point::Point(int x, int y) : _coordX(x), _coordY(y) {}
Point::Point(const Point& other) : _coordX(other._coordX), _coordY(other._coordY) {}

int Point::get_x() const {
	return _coordX;
}
int Point::get_y() const {
	return _coordY;
}
bool Point::operator ==(const Point& other) const noexcept {
	return(_coordX == other.get_x() && _coordY == other.get_y());
}
