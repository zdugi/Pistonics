#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <SDL2/SDL.h>
#include "Rectangle.h"
#include "BoundBox.h"
#include "GameObject2D.h"

namespace Pistonics {
	class Player : public Graphics::GameObject2D {

		const int PLAYER_VEL = 5;

		public:
			Player(	std::string name,
				int x,
				int y,
				int width,
				int height,
				SDL_Texture* texture,
				Collisions::BoundBox* topBox,
				Collisions::BoundBox* leftBox,
				Collisions::BoundBox* botBox,
				Collisions::BoundBox* rightBox);
			~Player();
			
			void controlHandler(SDL_Event e);
			void increaseScore(int value);
			int getScore();
			std::string getName();
			Graphics::Object2DFamily getType();
			void collisionTrigger(Graphics::Object2DSide side, 
					Graphics::Object2DFamily collideWith);

			// skarabudzeno
			bool quitRequested();
		private:
			std::string name;
			int score;
			Graphics::Object2DFamily family;

			// indicators
			bool obsticle;
			bool requestQuit;
	};
}

#endif
