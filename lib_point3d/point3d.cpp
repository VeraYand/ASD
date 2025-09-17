#include "point3d.h"

Point3D::Point3D(): Point(0, 0), _coordZ(0) {}
Point3D::Point3D(int x, int y, int z): Point(x, y), _coordZ(z) {}
Point3D::Point3D(const Point3D& other) : Point(other), _coordZ(other._coordZ) {}

int Point3D::get_z() const {
	return _coordZ;
}

bool Point3D::operator ==(const Point3D& other) const noexcept {
	return(Point::operator ==(other) && _coordZ == other.get_z());
}