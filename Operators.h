#ifndef OPERATORS_H
#define OPERATORS_H

#include <iostream>
#include "Polygon.h"
#include "AddStructs.h"
#include "Area.h"

std::istream& operator>>(std::istream& in, SeparatorIO&& dest);
std::istream& operator>>(std::istream& in, Point& point);
std::istream& operator>>(std::istream& in, Polygon& poly);
std::ostream& operator<<(std::ostream& out, const Point& point);
std::ostream& operator<<(std::ostream & out, const Polygon & poly);
std::ostream& operator<<(std::ostream& out, const Area& area);

#endif
