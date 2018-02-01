#include "Coin.h"

Pistonics::Coin::Coin(		int x,
				int y,
				int width,
				int height,
				int xMin,
				int xMax,
				int yMin,
				int yMax,
				SDL_Texture* texture,
				Collisions::BoundBox* topBox,
				Collisions::BoundBox* leftBox,
				Collisions::BoundBox* botBox,
				Collisions::BoundBox* rightBox)	:
	Graphics::GameObject2D(texture, new Geometry::Rectangle(x, y, width, height),
			       topBox, leftBox, botBox, rightBox) {
	// proba samo
	
	value = COIN_START_VALUE;
	std::srand(std::time(0));

	this->xMin = xMin;
	this->xMax = xMax;
	this->yMin = yMin;
	this->yMax = yMax;

	this->spawnBall = false;
}


Pistonics::Coin::~Coin() {
}


int Pistonics::Coin::getValue() {
	return value;
}


void Pistonics::Coin::increaseValue() {
	value += COIN_START_VALUE;
}


void Pistonics::Coin::randMove(int xMin, int xMax, int yMin, int yMax) {
	int x = xMin + rand() % (xMax - xMin);
	int y = yMin + rand() % (yMax - yMin);

	setPosition(x, y);	
}


Graphics::Object2DFamily Pistonics::Coin::getType() {
	return Graphics::Object2DFamily::COIN;
}


bool Pistonics::Coin::canSpawnBall() {
	if (spawnBall) {
		spawnBall = false;
		return true;
	}
	return spawnBall;
}


void Pistonics::Coin::collisionTrigger(Graphics::Object2DSide side, 
			Graphics::Object2DFamily collideWith) {
	switch (collideWith) {
		case Graphics::Object2DFamily::PLAYER:
			spawnBall = true;
			randMove(xMin, xMax, yMin, yMax);
			//printf("New position: %d, %d\n", getShape()->getX(), getShape()->getY());
			break;
	}
}
