#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include "Point.h"
#include "Polygon.h"
#include "Area.h"

double trianglArea(const Point& point_1, const Point& point_2, const Point& point_3);
double area(Polygon& poly);

Area areaEven(std::vector< Polygon >& poly);
Area areaOdd(std::vector< Polygon >& poly);
Area areaMean(std::vector< Polygon >& poly);
Area areaVert(std::vector< Polygon >& poly, const int& corn);

int countEven(std::vector< Polygon >& poly);
int countOdd(std::vector< Polygon >& poly);
int countVert(std::vector< Polygon >& poly, const int& corn);

Area maxArea(std::vector< Polygon >& poly);
int maxVert(std::vector< Polygon >& poly);

Area minArea(std::vector< Polygon >& poly);
int minVert(std::vector< Polygon >& poly);

//LESSAREA <Polygon> Команда подсчитывает количество фигур с площадью меньшей, чем площадь фигуры, переданной в параметре.
//MAXSEQ <Polygon> Подсчёт максимального количества идущих подряд фигур идентичной указанной в параметрах

#endif
