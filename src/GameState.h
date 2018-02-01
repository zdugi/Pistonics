#ifndef GAMESTATE_H
#define GAMESTATE_H

namespace Pistonics {
	class GameState {
		public:
			GameState(bool run);

			void setRunning(bool state);
			void setPaused(bool state);
			bool isRunning();
			bool isPaused();

		private:
			bool running = true;
			bool paused = false;
	};
}

#endif


