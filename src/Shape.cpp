#include "Shape.h"

Geometry::Shape::Shape(int x, int y) : x(x), y(y) {}


int Geometry::Shape::getX() {
	return x;
}


int Geometry::Shape::getY() {
	return y;
}


void Geometry::Shape::setX(int x) {
	this->x = x;
}


void Geometry::Shape::setY(int y) {
	this->y = y;
}
