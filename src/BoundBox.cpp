#include "BoundBox.h"
#include <cstdio>

Collisions::BoundBox::BoundBox(int x, int y, unsigned int width, unsigned int height) 
	: Rectangle(x, y, width, height) {
		toRender = false;
	}


Collisions::BoundBox::~BoundBox() {
}


bool Collisions::BoundBox::collideWith(BoundBox *bbox) {
	return intersect(bbox);
}


void Collisions::BoundBox::render(SDL_Renderer* gRenderer, int refX, int refY) {
	if (toRender) {
		SDL_Rect rect = {getX() + refX, getY() + refY, getWidth(), getHeight()};
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x0C, 0xFF); // set green color
		SDL_RenderFillRect(gRenderer, &rect);
	}
}


void Collisions::BoundBox::render(SDL_Renderer* gRenderer) {
	render(gRenderer, 0, 0);
}
