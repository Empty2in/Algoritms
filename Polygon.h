#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

namespace myspace {

	struct Point {
		int x, y;
	};

	struct Polygon {
		std::vector< Point > points;
	};

	struct Area {
		double ar;
	};
}

#endif
