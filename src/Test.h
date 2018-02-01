#ifndef TEST_H
#define TEST_H
#include <SDL2/SDL.h>
#include <vector>
#include "Display.h"
#include "BoundBox.h"
#include "CollisionEngine.h"
#include "Player.h"
#include "Wall.h"
#include "Enemy.h"
#include "Coin.h"
#include "AIOutput.h"

using namespace Graphics;
using namespace Collisions;

namespace Pistonics {
	const int EDGES = 4;
	class Test {
		public:
			Test();
			~Test();

			void run();
		private:
			Display* display;
			bool* isRunning;
			CollisionEngine* collisionEngine;
			AIIO::AIOutput* aiOutput;
			
			Player* player;
			Coin* coin;
			std::vector<Enemy*> enemies; // problematicno
			Wall* edges[EDGES];
			

			// labels
			Graphics::GLabel* fps;
			Graphics::GLabel* score;
	};
}
#endif
