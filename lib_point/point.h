#pragma once


class Point {
	int _coordX;
	int _coordY;
public:
	Point();
	Point(int x, int y);
	Point(const Point&);

	int get_x() const;
	int get_y() const;

	bool operator ==(const Point&) const noexcept;
};