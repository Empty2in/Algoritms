#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include <functional>
#include "Polygon.h"

namespace myspace {

	struct ifAreaEven {
		double operator() (double sum, const Polygon& poly);
	};
	struct ifAreaOdd {
		double operator()(double sum, const Polygon& poly);
	};
	struct ifAreaVert {
		double operator()(double sum, int corn, const Polygon& poly);
	};

	void evenOrOdd(Area& ar, const std::vector< Polygon >& poly, std::function< double(double, const Polygon&) > funct);
	bool isEmpty(const std::vector< Polygon >& poly);

	Area areaEven(const std::vector< Polygon >& poly);
	Area areaOdd(const std::vector< Polygon >& poly);
	Area areaMean(const std::vector< Polygon >& poly);
	Area areaVert(const std::vector< Polygon >& poly, int corn);

	int countEven(const std::vector< Polygon >& poly);
	int countOdd(const std::vector< Polygon >& poly);
	int countVert(const std::vector< Polygon >& poly, int corn);

	Area maxArea(const std::vector< Polygon >& poly);
	int maxVert(const std::vector< Polygon >& poly);

	Area minArea(const std::vector< Polygon >& poly);
	int minVert(const std::vector< Polygon >& poly);

	int lessArea(const Polygon& other, const std::vector< Polygon >& poly);
	int maxSeq(const Polygon& other, const std::vector< Polygon >& poly);

}

#endif
