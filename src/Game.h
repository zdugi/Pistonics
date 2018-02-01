#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "Display.h"
#include "BoundBox.h"
#include "CollisionEngine.h"
#include "Player.h"
#include "Wall.h"
#include "Enemy.h"
#include "Coin.h"
#include "AIOutput.h"

namespace Pistonics {
	const int NUM_EDGES_WALLS = 4;

	class Game {
		public:
			Game(std::string title, const unsigned int width, const unsigned int height);
			~Game();
			
			void run(); // game hearth
		private:
			Graphics::Display* display;
			Collisions::CollisionEngine* collisionEngine;
			//AIIO::AIOutput* aiOutput;
			
			Player* player;
			Coin* coin;
			std::vector<Enemy*> enemies; // problematicno
			Wall* edges[NUM_EDGES_WALLS];
	};
}

#endif
