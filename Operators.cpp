#include <algorithm>
#include <iomanip>
#include <sstream>
#include "Operators.h"
#include "StreamStruct.h"

namespace myspace {

    std::istream& operator>>(std::istream& in, SeparatorIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        char c = '0';
        in >> c;
        if (in && (c != dest.sep)) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, Point& point) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        int x = 0;
        int y = 0;
        in >> SeparatorIO{ '(' };
        if (!in) {
            return in;
        }
        in >> x;
        if (in.peek() == ',' || in.peek() == '.') {
            in.setstate(std::ios::failbit);
        }
        in >> SeparatorIO{ ';' };
        if (!in) {
            return in;
        }
        in >> y;
        if (in.peek() == ',' || in.peek() == '.') {
            in.setstate(std::ios::failbit);
        }
        in >> SeparatorIO{ ')' };
        if (!in) {
            return in;
        }
        if (in) {
            point.x = x;
            point.y = y;
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, Polygon& poly) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        Polygon temp;
        int corners = 0;
        in >> corners;
        if (corners == 0) {
            in.clear();
            in.ignore(1000, '\n');
            return in;
        }
        std::string str;
        std::getline(in, str, '\n');
        std::istringstream iss(str);
        std::copy(
            std::istream_iterator< Point >(iss),
            std::istream_iterator< Point >(),
            std::back_inserter(temp.points)
        );
        if (temp.points.size() != corners) {
            in.setstate(std::ios::failbit);
        }
        if (in) {
            poly = temp;
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const Point& point)
    {
        std::ostream::sentry sentry(out);
        if (!sentry) {
            return out;
        }
        StreamGuard stream(out);
        out << '(' << point.x << ';' << point.y << ')';
        return out;
    }

    std::ostream& operator<<(std::ostream& out, const Polygon& poly)
    {
        std::ostream::sentry sentry(out);
        if (!sentry) {
            return out;
        }
        StreamGuard stream(out);
        std::copy(
            std::begin(poly.points),
            std::end(poly.points),
            std::ostream_iterator< Point >(std::cout, " ")
        );
        return out;
    }

    std::ostream& operator<<(std::ostream& out, const Area& area)
    {
        std::ostream::sentry sentry(out);
        if (!sentry) {
            return out;
        }
        StreamGuard stream(out);
        std::cout << std::fixed << std::setprecision(1) << area.ar;
        return out;
    }

    bool operator==(const Polygon& poly1, const Polygon poly2)
    {
        if (poly1.points.size() != poly2.points.size()) {
            return false;
        }
        return std::equal(
            poly1.points.begin(),
            poly1.points.end(),
            poly2.points.begin()
        );
    }

    bool operator==(const Point& p1, const Point& p2)
    {
        return ((p1.x == p2.x) && (p1.y == p2.y));
    }
}
