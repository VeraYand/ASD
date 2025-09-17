#include "sphere.h"

Sphere::Sphere(): _centre(0, 0, 0), Circle(){}
Sphere::Sphere(Point3D centre, int radius): Circle(Point(centre.get_x(), centre.get_y()), radius), _centre(centre) {}
Sphere::Sphere(const Sphere& other): Circle(other), _centre(other._centre){}

Point3D Sphere::get_centre() const {
	return _centre;
}

bool Sphere::operator ==(const Sphere& other) const noexcept {
	return(Circle::operator==(other) && _centre == other.get_centre());
}