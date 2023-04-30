#include "Operators.h"
#include "StreamGuard.h"
#include <algorithm>
#include <iomanip>

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
    in >> x;
    if (in.peek() == ',' || in.peek() == '.') {
        in.setstate(std::ios::failbit);
    }
    in >> SeparatorIO{ ';' };
    in >> y;
    if (in.peek() == ',' || in.peek() == '.') {
        in.setstate(std::ios::failbit);
    }
    in >> SeparatorIO{ ')' };
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
    Point point;
    in >> point;
    if (in) {
        poly.points.push_back(point);
    }
    else {
        in.setstate(std::ios::failbit);
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
    std::for_each(poly.points.cbegin(), poly.points.cend(), 
        [](Point p) { std::cout << p << ' '; });
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
