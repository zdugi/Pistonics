#include "Player.h"


Pistonics::Player::Player( std::string name,
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
		this->name = name;
		score = 0;
		family = Graphics::Object2DFamily::PLAYER;

		requestQuit = false;

		obsticle = false;
	}

Pistonics::Player::~Player() {}



void Pistonics::Player::increaseScore(int value) {
	score += value;
}


void Pistonics::Player::controlHandler(SDL_Event e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
			case SDLK_UP:
				setVelY(-PLAYER_VEL);
			       	break;
			case SDLK_DOWN: setVelY(PLAYER_VEL); break;
			case SDLK_LEFT: setVelX(-PLAYER_VEL); break;
			case SDLK_RIGHT: setVelX(PLAYER_VEL); break;
		}
	} else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
			case SDLK_UP: setVelY(0); break;
			case SDLK_DOWN: setVelY(0); break;
			case SDLK_LEFT: setVelX(0); break;
			case SDLK_RIGHT: setVelX(0); break;
		}
	} 
}


int Pistonics::Player::getScore() {
	return score;
}


std::string Pistonics::Player::getName() {
	return name;
}


Graphics::Object2DFamily Pistonics::Player::getType() {
	return family;
}


void Pistonics::Player::collisionTrigger(Graphics::Object2DSide side, 
					Graphics::Object2DFamily collideWith) {
	// here handle collisions...
	//
	

	switch (collideWith) {
		case Graphics::Object2DFamily::WALL:
			{
				int step = PLAYER_VEL + 1;
				switch (side) {
					case Graphics::Object2DSide::TOP:
						move(0, step);
						break;
					case Graphics::Object2DSide::BOT:
						move(0, -step);
						break;
					case Graphics::Object2DSide::RIGHT:
						move(-step, 0);
						break;
					case Graphics::Object2DSide::LEFT:
						move(step, 0);
						break;
				}
			}
			break;
		case Graphics::Object2DFamily::ENEMY:
			requestQuit = true;
			break;
		case Graphics::Object2DFamily::COIN:
			//printf("Collected.\n");
			break;
	}
}


bool Pistonics::Player::quitRequested() {
	return requestQuit;
}
