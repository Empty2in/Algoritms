#ifndef FUNCTORS_H
#define FUNCTORS_H

#include "Polygon.h"

namespace myspace {

	double trianglArea(const Point& point_1, const Point& point_2, const Point& point_3);
	double area(const Polygon& poly);
	struct functArea {
		double operator()(double sum, const Point& point, const Polygon& poly, Point& firstP);
	};
}



#endif
