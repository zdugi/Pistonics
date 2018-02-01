#include "Rectangle.h"
#include <cstdio>

Geometry::Rectangle::Rectangle(int x, int y, int width, int height) : Geometry::Shape(x, y) {
	this->width = width;
	this->height = height;
}


int Geometry::Rectangle::getWidth() {
	return width;
}


int Geometry::Rectangle::getHeight() {
	return height;
}


SDL_Rect Geometry::Rectangle::getRenderQuad() {
	SDL_Rect rect = {Geometry::Shape::getX(), Geometry::Shape::getY(), width, height};
	return rect; 
}


bool Geometry::Rectangle::intersect(Rectangle* rec) {
	return getX() < rec->getX() + rec->getWidth() && getX() + getWidth() > rec->getX() &&
		getY() < rec->getY() + rec->getHeight() && getY() + getHeight() > rec->getY();
}
