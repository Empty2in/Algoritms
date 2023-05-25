#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include "Operators.h"
#include "Commands.h"

using myspace::Polygon;

const int IGNORE = 1000;

void invalid(std::fstream& in);
void openFile(std::fstream& in, std::string& fileName);
void printShapes(const std::vector< Polygon >& shapes);
void readShapes(std::fstream& in, std::vector< Polygon >& shapes);
void doCommands(std::fstream& in, std::vector< Polygon >& shapes);

int main() {
	std::fstream in;
	std::string fileName;
	try {
		openFile(in, fileName);
		std::vector< Polygon > shapes;
		readShapes(in, shapes);
		printShapes(shapes);
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
		std::copy_if(
			std::istream_iterator< Polygon >(in),
			std::istream_iterator< Polygon >(),
			std::back_inserter(shapes),
			[](const Polygon& poly)
			{ return poly.points.size() != 0; }
		);
		if (!in && !in.eof()) {
			in.clear();
		}
	}
	in.close();
}

void doCommands(std::fstream& in, std::vector< Polygon >& shapes) {
	while (!in.eof()) {
		std::string com1 = "";
		std::string com2 = "";
		in >> com1;
		if (in.peek() == '\n') {
			invalid(in);
		}
		else if (com1 == "AREA") {
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
			else if (std::all_of(com2.begin(), com2.end(), std::isdigit) && (com2 != "")) {
				std::cout << "AREA " << com2 << ": " << areaVert(shapes, std::stoi(com2)) << '\n';
			}
			else {
				invalid(in);
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
			else {
				invalid(in);
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
			else {
				invalid(in);
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
			else if (std::all_of(com2.begin(), com2.end(), std::isdigit) && (com2 != "")) {
				std::cout << "COUNT " << com2 << ": " << countVert(shapes, std::stoi(com2)) << '\n';
			}
			else {
				invalid(in);
			}
		}
		else if (com1 == "LESSAREA") {
			Polygon poly;
			in >> poly;
			if (!in) {
				invalid(in);
			}
			else {
				std::cout << "LESSAREA " << poly << ": " << lessArea(poly, shapes) << '\n';
			}
		}
		else if (com1 == "MAXSEQ") {
			Polygon poly;
			in >> poly;
			if (!in) {
				invalid(in);
			}
			else {
				std::cout << "MAXSEQ " << poly << ": " << maxSeq(poly, shapes) << '\n';
			}
		}
		else {
			invalid(in);
		}
	}
	in.close();
}

void printShapes(const std::vector< Polygon >& shapes) {
	std::copy(
		std::begin(shapes),
		std::end(shapes),
		std::ostream_iterator< Polygon >(std::cout, "\n")
	);
}

void invalid(std::fstream& in) {
	std::cerr << "INVALID COMMAND\n";
	in.clear();
	in.ignore(IGNORE, '\n');
}