#ifndef OPERATORS_H
#define OPERATORS_H

#include <iostream>
#include "Polygon.h"
#include "StreamStruct.h"

namespace myspace {

	std::istream& operator>>(std::istream& in, SeparatorIO&& dest);
	std::istream& operator>>(std::istream& in, Point& point);
	std::istream& operator>>(std::istream& in, Polygon& poly);
	std::ostream& operator<<(std::ostream& out, const Point& point);
	std::ostream& operator<<(std::ostream& out, const Polygon& poly);
	std::ostream& operator<<(std::ostream& out, const Area& area);

	bool operator==(const Polygon& poly1, const Polygon poly2);
	bool operator==(const Point& p1, const Point& p2);
}

#endif
