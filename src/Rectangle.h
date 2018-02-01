#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL2/SDL.h>
#include "Shape.h"

namespace Geometry {
	class Rectangle : public Shape {
		public:
			Rectangle(int x, int y, int width, int height);

			int getWidth();
			int getHeight();
			
			SDL_Rect getRenderQuad();
			bool intersect(Rectangle* rec);
		private:
			int width;
			int height;
	};
}

#endif
