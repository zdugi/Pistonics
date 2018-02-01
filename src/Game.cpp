#include "Game.h"
#include <SDL2/SDL.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>

// @piranje

Pistonics::Game::Game(std::string title, const unsigned int width, const unsigned int height) {
	display = new Graphics::Display(title, width, height);
	collisionEngine = new Collisions::CollisionEngine();

	// zasto ne oze u statickoj nego ovako samo ?!?!?!
	//edges = new Wall*[NUM_EDGES_WALLS];

	// ################ INIT ##################
	
	player = new Player("Zdravko", 100, 200, 32, 32, 
					display->loadTexture("hero.bmp"), 
					new Collisions::BoundBox(8, 1, 15, 3),
					new Collisions::BoundBox(1, 8, 3, 15),
					new Collisions::BoundBox(8, 27, 15, 3),
					new Collisions::BoundBox(27, 8, 3, 15));
	display->addObject(player);
	collisionEngine->addGO2D(player);

	const int EDGE_WALL_SIZE = 5;
	edges[0] = new Wall(0, 0,  display->getWidth(), EDGE_WALL_SIZE,
				NULL,
				new Collisions::BoundBox(0, 0, display->getWidth(), EDGE_WALL_SIZE),
				NULL,
				NULL,
				NULL);
	edges[1] = new Wall(0, 0, EDGE_WALL_SIZE, display->getHeight(),
				NULL,
				new Collisions::BoundBox(0, 0, EDGE_WALL_SIZE, display->getHeight()),
				NULL,
				NULL,
				NULL);
	edges[2] = new Wall(0, 0,  display->getWidth(), EDGE_WALL_SIZE,
				NULL,
				new Collisions::BoundBox(0, display->getHeight() -  EDGE_WALL_SIZE,
					display->getWidth(), EDGE_WALL_SIZE),
				NULL,
				NULL,
				NULL);
	edges[3] = new Wall(0, 0,  EDGE_WALL_SIZE, display->getHeight(),
				NULL,
				new Collisions::BoundBox(display->getWidth() - EDGE_WALL_SIZE, 0,
				       	EDGE_WALL_SIZE, display->getHeight()),
				NULL,
				NULL,
				NULL);
	for (int i = 0; i < NUM_EDGES_WALLS; i++) {
		display->addObject(edges[i]);
		collisionEngine->addGO2D(edges[i]);
	}

	coin = new Coin(40, 40, 16, 16, 20, display->getWidth() - 20, 20, display->getHeight() - 20,
			display->loadTexture("coin.bmp"),
			new Collisions::BoundBox(3, 1, 10, 3),
			new Collisions::BoundBox(1, 3, 3, 10),
			new Collisions::BoundBox(3, 13, 10, 3),
			new Collisions::BoundBox(13, 3, 3, 10));
	display->addObject(coin);
	collisionEngine->addGO2D(coin);
	// ########################################
	
	enemies.push_back(new Enemy(-ENEMY_VEL, ENEMY_VEL, 300, 300, 16, 16, display->loadTexture("enemy.bmp"),
			new Collisions::BoundBox(3, 1, 10, 3),
			new Collisions::BoundBox(1, 3, 3, 10),
			new Collisions::BoundBox(3, 13, 10, 3),
			new Collisions::BoundBox(13, 3, 3, 10)));
	display->addObject(enemies.back());
	collisionEngine->addGO2D(enemies.back());
}


Pistonics::Game::~Game() {
	printf("[Game] Destruct engine.\n");
	delete collisionEngine;
	collisionEngine = NULL;
	
	printf("[Game] Destruct player.\n");
	delete player;
	player = NULL;
	
	printf("[Game] Destruct coin.\n");
	delete coin;
	coin = NULL;
	
	printf("[Game] Destruct enemies.\n");
	for (std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
		delete (*it);

	printf("[Game] Destruct edges.\n");
	for (int i = 0; i < NUM_EDGES_WALLS; i++) {
		if (edges[i] == NULL) {
			printf("Sht\n");
			continue;
		}
	//	delete edges[i];
	}
	//delete[] edges;
	
	printf("[Game] Destruct display.\n");
	delete display;
	display = NULL;
}


void Pistonics::Game::run() {
	const int SCREEN_FPS = 60;
	const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
	long ltime = 0;
	bool running = true;
	SDL_Event e;
	
	while (running) {
		ltime = SDL_GetTicks();
		
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				running = false;
				
			}
			
			player->controlHandler(e);
		}

		// MOVE, HERE OR NOT?!
		player->move();
		for (std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++)
			(*it)->move();

		// COLLISIONS
		//collisionEngine->handler();

		if (coin->canSpawnBall()) {
			player->increaseScore(coin->getValue());
			printf("%s scored: %d\n", player->getName().c_str(), player->getScore());
			// something smarter, much smarter
			// @info for now experimental, i didn't include ctime and set srand, i use from enemy class :P BAD!
			int innerReg = 100;
			int cutReg = 300;
			int xs = innerReg+rand()%cutReg;
			int ys = innerReg+rand()%cutReg;
			//printf("(%d, %d)\n", xs, ys);
			enemies.push_back(new Enemy(ENEMY_VEL * (rand() % 2 ? -1 : 1), 
					ENEMY_VEL * (rand() % 2 ? -1 : 1), xs, ys,16, 16, display->loadTexture("enemy.bmp"),
			new Collisions::BoundBox(3, 1, 10, 3),
			new Collisions::BoundBox(1, 3, 3, 10),
			new Collisions::BoundBox(3, 13, 10, 3),
			new Collisions::BoundBox(13, 3, 3, 10)));
			display->addObject(enemies.back());
			collisionEngine->addGO2D(enemies.back());
		}
				
		// RENDERING
		display->render();


		// skarabudzotina
		if (player->quitRequested())
			running = false;
		
		// FRAMES AND TIME
		ltime = SDL_GetTicks() - ltime;
		if (ltime < SCREEN_TICK_PER_FRAME) {
			SDL_Delay(SCREEN_TICK_PER_FRAME - ltime);
		}
	}
}
