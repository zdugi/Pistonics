#include "CollisionEngine.h"
#include <cstdio>


Collisions::CollisionEngine::CollisionEngine() {
	numObjects = 0;
}


Collisions::CollisionEngine::~CollisionEngine() {
	// deleting objects is handled where they are created
	// in Game.cpp
}


bool Collisions::CollisionEngine::addGO2D(Graphics::GameObject2D *object) {
	// now is like: you cant remove objects from array
	BoundBox **boxes = object->getBoxes();

	if (MAX_OBJECTS - numObjects < Graphics::OBJECT_2D_SIDES) {
		printf("[Warning] Can't insertf GameObject2D to CollisionEngine.\n");
		return false;
	}

	for (int i = 0; i < Graphics::OBJECT_2D_SIDES; i++) {
		if (boxes[i] == NULL) continue;
		CollisionProcessPair* cpp = new CollisionProcessPair;
		cpp->parent = object;
		cpp->bbox = boxes[i];
		cpp->side = static_cast<Graphics::Object2DSide>(i);

		gameObjects[numObjects++] = cpp;
	}

	return true;
}


bool Collisions::CollisionEngine::handler() {
	/*
	 *	here will come collisions handling
	 */
	
	for (int i = 0; i < numObjects; i++) {
		for (int j = i + 1; j < numObjects; j++) {
			// skip bboxes of same object
			if (gameObjects[i]->parent == gameObjects[j]->parent) continue;
			// SAT implementation, try :P
			if (SATCollision(gameObjects[j]->bbox, gameObjects[i]->bbox) ||
					SATCollision(gameObjects[i]->bbox, gameObjects[j]->bbox)) {
				gameObjects[i]->parent->collisionTrigger(gameObjects[i]->side, 
					gameObjects[j]->parent->getType());
				gameObjects[j]->parent->collisionTrigger(gameObjects[j]->side, 
					gameObjects[i]->parent->getType());

			}
		}
	}

	return true;
}


bool Collisions::CollisionEngine::SATCollision(BoundBox* a, BoundBox* b) {
	// by x
	int aX1 = a->getX();
	int aX2 = aX1 + a->getWidth();
	int bX1 = b->getX();
	int bX2 = bX1 + b->getWidth();

	bool axX = false;
	bool axY = false;

	// by y
	int aY1 = a->getY();
	int aY2 = aY1 + a->getHeight();
	int bY1 = b->getY();
	int bY2 = bY1 + b->getHeight();

	if (dotBetween(aX1, bX1, bX2) || dotBetween(aX2, bX1, bX2))
		axX = true;

	if (dotBetween(aY1, bY1, bY2) || dotBetween(aY2, bY1, bY2))
		axY = true;

	return axX && axY;
}


bool Collisions::CollisionEngine::dotBetween(int dotA, int dotB, int dotC) {
	return dotA >= dotB && dotA <= dotC;
}
