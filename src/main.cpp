#include <cstdio>
#include <new>
//#include "Game.h"

#include "Test.h"

// @pitanje - postavio sam kao dinamicku promenljivo
// 	      game, i onda nije radio vektor u Game
using namespace Pistonics;

int main() {
	printf("Running...\n");
	
	Test* t = new Test();

	t->run();

	delete t; //@interest

	printf("Finished.\n");

	return 0;
}
