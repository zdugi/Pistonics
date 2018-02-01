#include "Enemy.h"


Pistonics::Enemy::Enemy( 	int velX,
				int velY,
				int x,
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
		setVelX(velX);
		setVelY(velY);
	}


Pistonics::Enemy::~Enemy() {}


Graphics::Object2DFamily Pistonics::Enemy::getType() {
	return Graphics::Object2DFamily::ENEMY;
}


void Pistonics::Enemy::collisionTrigger(Graphics::Object2DSide side, 
					Graphics::Object2DFamily collideWith) {
	// here handle collisions...
	//

	switch (collideWith) {
		case Graphics::Object2DFamily::WALL:
			switch (side) {
				case Graphics::Object2DSide::TOP:
					setVelY(-getVelY());
					break;
				case Graphics::Object2DSide::BOT:
					setVelY(-getVelY());
					break;
				case Graphics::Object2DSide::RIGHT:
					setVelX(-getVelX());
					break;
				case Graphics::Object2DSide::LEFT:
					setVelX(-getVelX());
					break;
			}
			break;
		
	}
}
