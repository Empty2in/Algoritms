#include <numeric>
#include <functional>
#include <algorithm>
#include "AreaFunc.h"
#include "Polygon.h"
#include "Operators.h"

using namespace std::placeholders;

namespace myspace {

	double functArea::operator()(double sum, const Point& point, const Polygon& poly, Point& firstP) {
		double area = trianglArea(firstP, point, *(poly.points.end() - 1));
		firstP = point;
		return sum + area;
	}

	double trianglArea(const Point& point_1, const Point& point_2, const Point& point_3) {
		double ar = 0.0;
		ar = 0.5 * abs((point_2.x - point_1.x) * (point_3.y - point_1.y)
			- (point_3.x - point_1.x) * (point_2.y - point_1.y));
		return ar;
	}

	double area(const Polygon& poly) {
		Point firstP = poly.points.front();
		double ans = std::accumulate(
			poly.points.begin() + 1,
			poly.points.end() - 1,
			0.0,
			std::bind(functArea(), _1, _2, poly, firstP)
		);
		return ans;
	}
}

