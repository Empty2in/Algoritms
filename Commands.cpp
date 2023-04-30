#include "Commands.h"
#include <iostream>
#include <math.h>
#include <numeric>
#include <algorithm>

double trianglArea(const Point& point_1, const Point& point_2, const Point& point_3) {
	double ar = 0.0;
	ar = 0.5 * abs((point_2.x - point_1.x) * (point_3.y - point_1.y)
		- (point_3.x - point_1.x) * (point_2.y - point_1.y));
	return ar;
}
double area(Polygon& poly) {
	double ar = 0.0;
	int j = 1;
	for (int i = 0; i < poly.points.size() - 2; ++i) {
		ar += trianglArea(poly.points[0], poly.points[j], poly.points[j + 1]);
		j++;
	}
	return ar;
}

Area areaEven(std::vector< Polygon >& poly) {
	Area ar{};
	for (auto i = poly.begin(); i != poly.end(); ++i) {
		auto ans = std::find_if(i, poly.end(),
			[](Polygon poly) { return poly.points.size() % 2 != 0; });
		if (ans != poly.end()) {
			ar.ar += area(*ans);
			i = ans;
		}
		else {
			break;
		}
	}
	return ar;
}

Area areaOdd(std::vector< Polygon >& poly) {
	Area ar{};
	for (auto i = poly.begin(); i != poly.end(); ++i) {
		auto ans = std::find_if(i, poly.end(),
			[](Polygon poly) { return poly.points.size() % 2 == 0; });
		if (ans != poly.end()) {
			ar.ar += area(*ans);
			i = ans;
		}
		else {
			break;
		}
	}
	return ar;
}

Area areaMean(std::vector<Polygon>& poly)
{
	Area ans{};
	ans.ar = std::accumulate(poly.cbegin(), poly.cend(), 0.0,
		[](double a, Polygon p) { return a + area(p); });
	ans.ar /= poly.size();
	return ans;
}

Area areaVert(std::vector<Polygon>& poly, const int& corn)
{
	Area ar{};
	for (auto i = poly.begin(); i != poly.end(); ++i) {
		auto ans = std::find_if(i, poly.end(),
			[corn](Polygon poly) { return poly.points.size() == corn; });
		if (ans != poly.end()) {
			ar.ar += area(*ans);
			i = ans;
		}
		else {
			break;
		}
	}
	return ar;
}

int countEven(std::vector<Polygon>& poly)
{
	int ans = std::count_if(poly.cbegin(), poly.cend(),
		[](Polygon p) { return p.points.size() % 2 != 0; });
	return ans;
}

int countOdd(std::vector<Polygon>& poly)
{
	int ans = std::count_if(poly.cbegin(), poly.cend(),
		[](Polygon p) { return p.points.size() % 2 == 0; });
	return ans;
}

int countVert(std::vector<Polygon>& poly, const int& corn)
{
	int ans = std::count_if(poly.cbegin(), poly.cend(),
		[corn](Polygon p) { return p.points.size() == corn; });
	return ans;
}

Area maxArea(std::vector<Polygon>& poly)
{
	auto temp = std::max_element(poly.begin(), poly.end(), 
		[](Polygon p1, Polygon p2) { return area(p1) < area(p2); });
	Area ans{ area(*temp) };
	return ans;
}

int maxVert(std::vector<Polygon>& poly)
{
	auto ans = std::max_element(poly.cbegin(), poly.cend(),
		[](Polygon p1, Polygon p2) { return p1.points.size() < p2.points.size(); });
	return (*ans).points.size();
}

Area minArea(std::vector<Polygon>& poly)
{
	auto temp = std::min_element(poly.begin(), poly.end(),
		[](Polygon p1, Polygon p2) { return area(p1) < area(p2); });
	Area ans{ area(*temp) };
	return ans;
}

int minVert(std::vector<Polygon>& poly)
{
	auto ans = std::min_element(poly.cbegin(), poly.cend(),
		[](Polygon p1, Polygon p2) { return p1.points.size() < p2.points.size(); });
	return (*ans).points.size();
}
