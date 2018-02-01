#include "Test.h"

Pistonics::Test::Test() {
	display = new Graphics::Display("Pistonics", 640, 480);
	collisionEngine = new Collisions::CollisionEngine();
	aiOutput = new AIIO::AIOutput("output.out");

	fps = display->createLabel("FPS:", 10, 10);
	score = display->createLabel("Score:", 10, 40);

	isRunning = new bool;
	*isRunning = true;
	
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
	aiOutput->addOutData(player);

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
	for (int i = 0; i < EDGES; i++) {
		display->addObject(edges[i]);
		collisionEngine->addGO2D(edges[i]);
		aiOutput->addOutData(edges[i]);
	}

	coin = new Coin(40, 40, 16, 16, 20, display->getWidth() - 20, 20, display->getHeight() - 20,
			display->loadTexture("coin.bmp"),
			new Collisions::BoundBox(3, 1, 10, 3),
			new Collisions::BoundBox(1, 3, 3, 10),
			new Collisions::BoundBox(3, 13, 10, 3),
			new Collisions::BoundBox(13, 3, 3, 10));
	display->addObject(coin);
	collisionEngine->addGO2D(coin);
	aiOutput->addOutData(coin);
	// ########################################
	
	enemies.push_back(new Enemy(-ENEMY_VEL, ENEMY_VEL, 300, 300, 16, 16, display->loadTexture("enemy.bmp"),
			new Collisions::BoundBox(3, 1, 10, 3),
			new Collisions::BoundBox(1, 3, 3, 10),
			new Collisions::BoundBox(3, 13, 10, 3),
			new Collisions::BoundBox(13, 3, 3, 10)));
	display->addObject(enemies.back());
	collisionEngine->addGO2D(enemies.back());
	aiOutput->addOutData(enemies.back());
}


Pistonics::Test::~Test() {
	delete collisionEngine;
	delete aiOutput;
	delete player;
	delete coin;
	
	for (std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end();
			it++)
		delete (*it);
	for (int i = 0; i < EDGES; i++)
		delete edges[i];
	delete display;
}


void Pistonics::Test::run() {
	SDL_Event e;

	// FRAMES
	const int SCREEN_FPS = 60;
	const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
	long ltime = 0, rtime = 0;

		
	//long obrisiMe = 0;

	while (*isRunning) {
		ltime = SDL_GetTicks();
		//obrisiMe++;
		
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				*isRunning = false;
				
			}
			
			player->controlHandler(e);
		}
		
		// MOVE
		player->move();
		for (std::vector<Enemy*>::iterator it = enemies.begin();
				it != enemies.end(); it++)
			(*it)->move();
	
		// COLLISION
		collisionEngine->handler();

		// IF COLLECT
		if (coin->canSpawnBall()) {
			player->increaseScore(coin->getValue());
			score->text = "Score: " + std::to_string(player->getScore());
			// something smarter, much smarter
			// @info for now experimental, 
			// i didn't include ctime and set srand, i use from enemy class :P BAD!
			int innerReg = 100;
			int cutReg = 300;
			int xs = innerReg+rand()%cutReg;
			int ys = innerReg+rand()%cutReg;
			//printf("(%d, %d)\n", xs, ys);
			enemies.push_back(new Enemy(ENEMY_VEL * (rand() % 2 ? -1 : 1), 
					ENEMY_VEL * (rand() % 2 ? -1 : 1),
				       	xs, ys,16, 16, display->loadTexture("enemy.bmp"),
			new Collisions::BoundBox(3, 1, 10, 3),
			new Collisions::BoundBox(1, 3, 3, 10),
			new Collisions::BoundBox(3, 13, 10, 3),
			new Collisions::BoundBox(13, 3, 3, 10)));
			display->addObject(enemies.back());
			collisionEngine->addGO2D(enemies.back());
			aiOutput->addOutData(enemies.back());
		}

		// AI OUTPUT
		//if (obrisiMe % 30 == 0) {
		//	obrisiMe = 0;
		//	printf("Printa\n");
		//	aiOutput->writeData();
		//}
		


		// RENDER
		display->render();

		// skarabudzotina - player is dead
		if (player->quitRequested())
			*isRunning = false;

		// FRAMES AND TIME
		rtime = SDL_GetTicks() - ltime;

		if (rtime < SCREEN_TICK_PER_FRAME) {
			SDL_Delay(SCREEN_TICK_PER_FRAME - rtime);
		}

		fps->text = "FPS: " + std::to_string(1000/(SDL_GetTicks() - ltime));
	}
}
