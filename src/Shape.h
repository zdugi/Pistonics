#ifndef SHAPE_H
#define SHAPE_H

#include <SDL2/SDL.h>

namespace Geometry {
	class Shape {
		public:
			Shape(int x, int y);
			
			int getX();
			int getY();

			void setX(int x);
			void setY(int y);

			virtual SDL_Rect getRenderQuad() = 0; // generate depend on shape
		private:
			int x = 0;
			int y = 0;
	};
}

#endif
