#include <iostream>
#include <math.h>
#include <numeric>
#include <algorithm>
#include <functional>
#include "Commands.h"
#include "Operators.h"
#include "AreaFunc.h"

using namespace std::placeholders;

namespace myspace {

	double ifAreaEven::operator()(double sum, const Polygon& poly) {
		if (poly.points.size() % 2 != 0) {
			return sum + area(poly);
		}
		return sum;
	}

	double ifAreaOdd::operator()(double sum, const Polygon& poly) {
		if (poly.points.size() % 2 == 0) {
			return sum + area(poly);
		}
		return sum;
	}

	double ifAreaVert::operator()(double sum, int corn, const Polygon& poly) {
		if (poly.points.size() == corn) {
			return sum + area(poly);
		}
		return sum;
	}

	bool isEmpty(const std::vector< Polygon >& poly) {
		return (poly.size() == 0);
	}

	void evenOrOdd(Area& ar, const std::vector< Polygon >& poly, std::function< double(double, const Polygon&) > funct) {
		ar.ar = std::accumulate(
			poly.begin(),
			poly.end(),
			0.0,
			std::bind(funct, _1, _2)
		);
	}

	Area areaEven(const std::vector< Polygon >& poly) {
		Area ar{};
		if (isEmpty(poly)) {
			return ar;
		}
		evenOrOdd(ar, poly, ifAreaEven());
		return ar;
	}

	Area areaOdd(const std::vector< Polygon >& poly) {
		Area ar{};
		if (isEmpty(poly)) {
			return ar;
		}
		evenOrOdd(ar, poly, ifAreaOdd());
		return ar;
	}

	Area areaMean(const std::vector< Polygon >& poly) {
		Area ar{};
		if (isEmpty(poly)) {
			return ar;
		}
		ar.ar = std::accumulate(
			poly.cbegin(), 
			poly.cend(), 
			0.0,
			[](double sum, const Polygon& p)
			{ return sum + area(p); }
		);
		ar.ar /= poly.size();
		return ar;
	}

	Area areaVert(const std::vector< Polygon >& poly, int corn) {
		Area ar{};
		if (isEmpty(poly)) {
			return ar;
		}
		ar.ar = std::accumulate(
			poly.begin(),
			poly.end(),
			0.0,
			std::bind(ifAreaVert(), _1, corn, _2)
		);
		return ar;
	}

	int countEven(const std::vector< Polygon >& poly) {
		if (isEmpty(poly)) {
			return 0;
		}
		__int64 ans = std::count_if(
			poly.cbegin(), 
			poly.cend(),
			[](const Polygon& p)
			{ return p.points.size() % 2 != 0; }
		);
		return static_cast<int>(ans);
	}

	int countOdd(const std::vector< Polygon >& poly) {
		if (isEmpty(poly)) {
			return 0;
		}
		__int64 ans = std::count_if(
			poly.cbegin(), 
			poly.cend(),
			[](const Polygon& p)
			{ return p.points.size() % 2 == 0; }
		);
		return static_cast<int>(ans);
	}

	int countVert(const std::vector< Polygon >& poly, int corn) {
		if (isEmpty(poly)) {
			return 0;
		}
		__int64 ans = std::count_if(
			poly.cbegin(), 
			poly.cend(),
			[corn](const Polygon& p)
			{ return p.points.size() == corn; }
		);
		return static_cast<int>(ans);
	}

	Area maxArea(const std::vector< Polygon >& poly) {
		Area ar{};
		if (isEmpty(poly)) {
			return ar;
		}
		auto temp = std::max_element(
			poly.begin(), 
			poly.end(),
			std::bind(
				std::less< int >{},
				std::bind(area, _1),
				std::bind(area, _2)
			)
		);
		ar.ar = area(*temp);
		return ar;
	}

	int maxVert(const std::vector< Polygon >& poly) {
		if (isEmpty(poly)) {
			return 0;
		}
		auto ans = std::max_element(
			poly.cbegin(), 
			poly.cend(),
			[](const Polygon& p1, const Polygon& p2)
			{ return p1.points.size() < p2.points.size(); }
		);
		return static_cast<int>((*ans).points.size());
	}

	Area minArea(const std::vector< Polygon >& poly) {
		Area ar{};
		if (isEmpty(poly)) {
			return ar;
		}
		auto temp = std::min_element(
			poly.begin(), 
			poly.end(),
			std::bind(
				std::less< int >{},
				std::bind(area, _1),
				std::bind(area, _2)
			)
		);
		ar.ar = area(*temp);
		return ar;
	}

	int minVert(const std::vector< Polygon >& poly) {
		if (isEmpty(poly)) {
			return 0;
		}
		auto ans = std::min_element(
			poly.cbegin(), 
			poly.cend(),
			[](const Polygon& p1, const Polygon& p2)
			{ return p1.points.size() < p2.points.size(); }
		);
		return static_cast<int>((*ans).points.size());
	}

	int lessArea(const Polygon& other, const std::vector< Polygon >& poly) {
		if (isEmpty(poly)) {
			return 0;
		}
		Area otherArea{ area(other) };
		__int64 ans = std::count_if(
			poly.cbegin(), 
			poly.cend(),
			std::bind(
				std::less< int >{},
				std::bind(area, _1),
				otherArea.ar
			)
		);
		return static_cast<int>(ans);
	}

	int maxSeq(const Polygon& other, const std::vector< Polygon >& poly) {
		if (isEmpty(poly)) {
			return 0;
		}
		int maxim = 0;
		auto ans = std::accumulate(
			poly.begin(),
			poly.end(),
			0,
			[&maxim, &other](int sum, const Polygon& p) {
				if (p == other) {
					sum++;
				}
				else {
					maxim = std::max(sum, maxim);
					sum = 0;
				}
				return sum;
			}
		);
		return maxim;
	}
}
