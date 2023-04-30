#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include "Operators.h"
#include "Commands.h"


void openFile(std::fstream& in, std::string& fileName);
void readShapes(std::fstream& in, std::vector< Polygon >& shapes);
void doCommands(std::fstream& in, std::vector< Polygon >& shapes);

int main() {
	std::fstream in;
	std::string fileName;
	try {
		openFile(in, fileName);
		std::vector< Polygon > shapes;
		readShapes(in, shapes);

		std::for_each(shapes.cbegin(), shapes.cend(),
			[](Polygon p) { std::cout << p << p.points.size() << '\n'; });

		openFile(in, fileName);
		doCommands(in, shapes);
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
		exit(-1);
	}

	return 0;
}

void openFile(std::fstream& in, std::string& fileName) {
	std::cout << "Enter name of file: ";
	std::cin >> fileName;
	in.open(fileName);
	if (!in.is_open()) {
		throw std::exception("Incorrrect name of file.");
	}
	if (in.peek() == EOF) {
		throw std::exception("file is empty.");
	}
}

void readShapes(std::fstream& in, std::vector< Polygon >& shapes) {
	while (!in.eof()) {
		int corners = 0;
		in >> corners;
		if (in.peek() == '.' || in.peek() == ',') {
			throw std::exception("incorrect count of corner.");
		}
		Polygon poly;
		/*std::copy(
			std::istream_iterator<Polygon>(in),
			std::istream_iterator<Polygon>(),
			std::back_inserter(poly)
		);*/
		for (int i = 0; i < corners; ++i) {
			in >> poly;
		}
		if (!in) {
			in.clear();
			in.ignore();
		}
		else {
			shapes.push_back(poly);
		}
	}
	in.close();
}

void doCommands(std::fstream& in, std::vector< Polygon >& shapes) {
	while (!in.eof()) {
		std::string com1 = "";
		std::string com2 = "";
		in >> com1;
		if (com1 == "AREA") {
			in >> com2;
			if (com2 == "EVEN") {
				std::cout << "AREA EVEN: " << areaEven(shapes) << '\n';
			}
			else if (com2 == "ODD") {
				std::cout << "AREA ODD: " << areaOdd(shapes) << '\n';
			}
			else if (com2 == "MEAN") {
				std::cout << "AREA MEAN: " << areaMean(shapes) << '\n';
			}
			else if (std::all_of(com2.begin(), com2.end(), ::isdigit)) {
				std::cout << "AREA " << com2 << ": " << areaVert(shapes, std::stoi(com2)) << '\n';
			}
		}
		else if (com1 == "MAX") {
			in >> com2;
			if (com2 == "AREA") {
				std::cout << "MAX AREA: " << maxArea(shapes) << '\n';
			}
			else if (com2 == "VERTEXES") {
				std::cout << "MAX VERTEXES: " << maxVert(shapes) << '\n';
			}
		}
		else if (com1 == "MIN") {
			in >> com2;
			if (com2 == "AREA") {
				std::cout << "MIN AREA: " << minArea(shapes) << '\n';
			}
			else if (com2 == "VERTEXES") {
				std::cout << "MIN VERTEXES: " << minVert(shapes) << '\n';
			}
		}
		else if (com1 == "COUNT") {
			in >> com2;
			if (com2 == "EVEN") {
				std::cout << "COUNT EVEN: " << countEven(shapes) << '\n';
			}
			else if (com2 == "ODD") {
				std::cout << "COUNT ODD: " << countOdd(shapes) << '\n';
			}
			else if (std::all_of(com2.begin(), com2.end(), ::isdigit)) {
				std::cout << "COUNT " << com2 << ": " << countVert(shapes, std::stoi(com2)) << '\n';
			}
		}
		else {
			std::cerr << "INVALID COMMAND\n";
			in.clear();
			in.ignore();
		}
	}
	in.close();
}
	
	//LESSAREA <Polygon> Команда подсчитывает количество фигур с площадью меньшей, чем площадь фигуры, переданной в параметре.
	//MAXSEQ <Polygon> Подсчёт максимального количества идущих подряд фигур идентичной указанной в параметрах