#include "Wall.h"
#include <cstdio>

Pistonics::Wall::Wall(int x,
				int y,
				int width,
				int height,
				SDL_Texture* texture,
				Collisions::BoundBox* topBox,
				Collisions::BoundBox* leftBox,
				Collisions::BoundBox* botBox,
				Collisions::BoundBox* rightBox) :
	Graphics::GameObject2D(texture, new Geometry::Rectangle(x, y, width, height),
			       topBox, leftBox, botBox, rightBox) {
		family = Graphics::Object2DFamily::WALL;
	}

Pistonics::Wall::~Wall() {
//	printf("[Wall] Calling destructor.\n");
}


Graphics::Object2DFamily Pistonics::Wall::getType() {
	return family;
}


void Pistonics::Wall::collisionTrigger(Graphics::Object2DSide side, 
					Graphics::Object2DFamily collideWith) {
	// here handle collisions...
}
