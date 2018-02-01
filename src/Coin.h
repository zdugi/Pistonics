#ifndef COIN_H
#define COIN_H

#include <SDL2/SDL.h>
#include "GameObject2D.h"
#include "Rectangle.h"
#include "BoundBox.h"
#include <ctime>

namespace Pistonics {

	const int COIN_START_VALUE = 2;

	class Coin : public Graphics::GameObject2D {
		public:
			Coin(	int x,
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
				Collisions::BoundBox* rightBox);
			~Coin();

			int getValue();
			void increaseValue();
			void randMove(int xMin, int xMax, int yMin, int yMax);
			bool canSpawnBall(); 


			Graphics::Object2DFamily getType();
			void collisionTrigger(Graphics::Object2DSide side, 
					Graphics::Object2DFamily collideWith);

		private:
			int value;
			int xMin;
			int xMax;
			int yMin;
			int yMax;
			bool spawnBall;
	};
}

#endif
