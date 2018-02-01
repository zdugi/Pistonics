#ifndef GAMEOBJECT2D_H
#define GAMEOBJECT2D_H

#include <SDL2/SDL.h>
#include "Shape.h"
#include "Rectangle.h"
#include "BoundBox.h"

namespace Graphics {
	const int OBJECT_2D_SIDES = 4;

	enum Object2DSide {TOP = 0, LEFT, BOT, RIGHT};
	enum Object2DFamily {COIN, PLAYER, ENEMY, WALL}; // REGISTER REAL GAME OBJECTS

	class GameObject2D {
		public:
			GameObject2D(SDL_Texture *gTexture, Geometry::Shape *shape,
					Collisions::BoundBox *topBox, Collisions::BoundBox *leftBox,
					Collisions::BoundBox *botBox, Collisions::BoundBox *rightBox);
			GameObject2D(GameObject2D& go2d);
			GameObject2D(const GameObject2D& go2d);
			~GameObject2D();

			void render(SDL_Renderer *gRenderer);

			void move();

			void setVelX(int velX);
			void setVelY(int velY);

			int getVelX();
			int getVelY();
			
			void move(int x, int y); 

			void setPosition(int x, int y);

			SDL_Texture *getTexture();
			Geometry::Shape *getShape();

			Collisions::BoundBox** getBoxes();

			// some more functions like move for x pixels or something
			// change color etc...

			virtual Object2DFamily getType() = 0;
			// maybe is better to pass GO2D* witch is collided for all info, but ok
			virtual void collisionTrigger(Object2DSide side, Object2DFamily collideWith) = 0;
		private:
			SDL_Texture *gTexture;
			Geometry::Shape *shape;
			Collisions::BoundBox *boxes[OBJECT_2D_SIDES];

			int velX;
			int velY;
	};
}

#endif
