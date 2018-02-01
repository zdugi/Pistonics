#include "GameState.h"

Pistonics::GameState::GameState(bool run) {
	running = run;
	paused = false;
}

void Pistonics::GameState::setRunning(bool state) {
	running = state;
}


void Pistonics::GameState::setPaused(bool state) {
	paused = state;
}


bool Pistonics::GameState::isRunning() {
	return running;
}


bool Pistonics::GameState::isPaused() {
	return paused;
}
