#ifndef WALL_H
#define WALL_H

#include "GameObject2D.h"
#include "BoundBox.h"

namespace Pistonics {
	class Wall : public Graphics::GameObject2D {
		public:
			Wall(int x,
				int y,
				int width,
				int height,
				SDL_Texture* texture,
				Collisions::BoundBox* topBox,
				Collisions::BoundBox* leftBox,
				Collisions::BoundBox* botBox,
				Collisions::BoundBox* rightBox);
			~Wall();

			Graphics::Object2DFamily getType();
			void collisionTrigger(Graphics::Object2DSide side, 
					Graphics::Object2DFamily collideWith);
		private:
			Graphics::Object2DFamily family;

	};
}

#endif
