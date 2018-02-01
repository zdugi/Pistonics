#ifndef COLLISION_ENGINE_H
#define COLLISION_ENGINE_H

#include "GameObject2D.h"
#include "BoundBox.h"

namespace Collisions {
	// experimental, maybe static for now, later dynamic
	const int MAX_OBJECTS = 512;

	struct CollisionProcessPair {
		Graphics::GameObject2D *parent;
		BoundBox *bbox;
		Graphics::Object2DSide side;
	};


	class CollisionEngine {
		public:
			CollisionEngine();
			~CollisionEngine();

			bool addGO2D(Graphics::GameObject2D *object);
			bool handler(); // handle collisions

			bool SATCollision(BoundBox* a, BoundBox* b);
			bool dotBetween(int dotA, int dotB, int dotC);
		private:
			int numObjects;
			struct CollisionProcessPair *gameObjects[MAX_OBJECTS];
	};
}

#endif
