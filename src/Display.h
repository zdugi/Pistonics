#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#include <cstdio>
#include <string>
#include <exception>
#include <vector>
#include <stack>
#include <new> // maybe

#include "GameObject2D.h"
#include "TextRenderEngine.h"

namespace Graphics {

	struct GLabel {
		std::string text;
		int x;
		int y;
	};

	class Display {
		public:
			Display(std::string title, unsigned int width, unsigned int height);
			~Display();


			void render();
			void addObject(GameObject2D* object2D);
			unsigned int getWidth();
			unsigned int getHeight();

			GLabel* createLabel(std::string text, int x, int y);

			SDL_Texture* loadTexture(std::string path);
		private:
			SDL_Window* gWindow = NULL;
			SDL_Renderer* gRenderer = NULL;
			TextRenderEngine* tre = NULL;
			std::vector<GLabel*> labels;
			std::vector<GameObject2D*> gameObjects;

			std::string title;
			unsigned int SCREEN_WIDTH, SCREEN_HEIGHT;
	};
}

#endif
