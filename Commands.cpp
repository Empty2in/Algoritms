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

	Area areaEven(const std::vector< Polygon >& poly) {
		Area ar{};
		ar.ar = std::accumulate(
			poly.begin(),
			poly.end(),
			0.0,
			std::bind(ifAreaEven(), _1, _2)
		);
		return ar;
	}

	Area areaOdd(const std::vector< Polygon >& poly) {
		Area ar{};
		ar.ar = std::accumulate(
			poly.begin(),
			poly.end(),
			0.0,
			std::bind(ifAreaOdd(), _1, _2)
		);
		return ar;
	}

	Area areaMean(const std::vector< Polygon >& poly) {
		Area ans{};
		ans.ar = std::accumulate(
			poly.cbegin(), 
			poly.cend(), 
			0.0,
			[](double sum, const Polygon& p)
			{ return sum + area(p); }
		);
		ans.ar /= poly.size();
		return ans;
	}

	Area areaVert(const std::vector< Polygon >& poly, int corn) {
		Area ar{};
		ar.ar = std::accumulate(
			poly.begin(),
			poly.end(),
			0.0,
			std::bind(ifAreaVert(), _1, corn, _2)
		);
		return ar;
	}

	int countEven(const std::vector< Polygon >& poly) {
		__int64 ans = std::count_if(
			poly.cbegin(), 
			poly.cend(),
			[](const Polygon& p)
			{ return p.points.size() % 2 != 0; }
		);
		return static_cast<int>(ans);
	}

	int countOdd(const std::vector< Polygon >& poly) {
		__int64 ans = std::count_if(
			poly.cbegin(), 
			poly.cend(),
			[](const Polygon& p)
			{ return p.points.size() % 2 == 0; }
		);
		return static_cast<int>(ans);
	}

	int countVert(const std::vector< Polygon >& poly, int corn) {
		__int64 ans = std::count_if(
			poly.cbegin(), 
			poly.cend(),
			[corn](const Polygon& p)
			{ return p.points.size() == corn; }
		);
		return static_cast<int>(ans);
	}

	Area maxArea(const std::vector< Polygon >& poly) {
		auto temp = std::max_element(
			poly.begin(), 
			poly.end(),
			[](const Polygon& p1,const Polygon& p2)
			{ return area(p1) < area(p2); }
		);
		Area ans{ area(*temp) };
		return ans;
	}

	int maxVert(const std::vector< Polygon >& poly) {
		auto ans = std::max_element(
			poly.cbegin(), 
			poly.cend(),
			[](const Polygon& p1, const Polygon& p2)
			{ return p1.points.size() < p2.points.size(); }
		);
		return static_cast<int>((*ans).points.size());
	}

	Area minArea(const std::vector< Polygon >& poly) {
		auto temp = std::min_element(
			poly.begin(), 
			poly.end(),
			[](const Polygon& p1, const Polygon& p2)
			{ return area(p1) < area(p2); }
		);
		Area ans{ area(*temp) };
		return ans;
	}

	int minVert(const std::vector< Polygon >& poly) {
		auto ans = std::min_element(
			poly.cbegin(), 
			poly.cend(),
			[](const Polygon& p1, const Polygon& p2)
			{ return p1.points.size() < p2.points.size(); }
		);
		return static_cast<int>((*ans).points.size());
	}

	int lessArea(const Polygon& other, const std::vector< Polygon >& poly) {
		Area otherArea{ area(other) };
		__int64 ans = std::count_if(
			poly.cbegin(), 
			poly.cend(),
			[&otherArea](const Polygon& p)
			{ return area(p) < otherArea.ar; }
		);
		return static_cast<int>(ans);
	}

	int maxSeq(const Polygon& other, const std::vector< Polygon >& poly) {
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
