#ifndef BOUNDBOX_H
#define BOUNDBOX_H

#include <SDL2/SDL.h>
#include "Rectangle.h"

namespace Collisions {
	
	class BoundBox : public Geometry::Rectangle {
		public:
			BoundBox(int x, int y, unsigned int width, unsigned int height);
			~BoundBox();

			bool collideWith(BoundBox *bbox);
			
			void render(SDL_Renderer* gRenderer, int refX, int refY);
			void render(SDL_Renderer* gRenderer);
		private:
			bool toRender;
	};
}

#endif
