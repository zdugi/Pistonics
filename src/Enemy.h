#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <SDL2/SDL.h>
#include "Rectangle.h"
#include "BoundBox.h"
#include "GameObject2D.h"

namespace Pistonics {
	const int ENEMY_VEL = 3;

	class Enemy : public Graphics::GameObject2D {
		public:
			Enemy( 	int velX,
				int velY,
				int x,
				int y,
				int width,
				int height,
				SDL_Texture* texture,
				Collisions::BoundBox* topBox,
				Collisions::BoundBox* leftBox,
				Collisions::BoundBox* botBox,
				Collisions::BoundBox* rightBox);
			~Enemy();
			
			Graphics::Object2DFamily getType();
			void collisionTrigger(Graphics::Object2DSide side, 
					Graphics::Object2DFamily collideWith);
		private:
			// game state handler
	};
}

#endif
