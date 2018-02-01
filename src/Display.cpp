#include "Display.h"
#include <cstdio>

Graphics::Display::Display(std::string title, unsigned int width, unsigned int height) {
	this->title = title;
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		//throw("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		throw(SDL_GetError());
	} else {
		
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1" /* 0-2 quality */)) {
			printf("[Warning] Linear texture filtering not enabled!");
		}

		gWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
			throw(SDL_GetError());
		else {
			if (TTF_Init() == -1)
				throw(TTF_GetError());

			
			gRenderer = SDL_CreateRenderer(gWindow,
				       -1,
				       SDL_RENDERER_ACCELERATED); // much better
			
			if (gRenderer == NULL)
				throw(SDL_GetError());
			else {
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}

			SDL_Color color = {0, 0, 0};
			tre = new TextRenderEngine(gRenderer, "oswald.ttf", color, 20);
		}
	}
}


Graphics::Display::~Display() {
	//deleted where created
	//for (std::vector<GameObject2D*>::iterator it = gameObjects.begin();
	//	       	it != gameObjects.end(); it++) {
	//	delete (*it);
	//}

	for (std::vector<Graphics::GLabel*>::iterator it = labels.begin();
		       	it != labels.end(); it++) {
		delete (*it);
	}

	delete tre;
	tre = NULL;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	
	gWindow = NULL;
	gRenderer = NULL;

	TTF_Quit();
	SDL_Quit();
}



void Graphics::Display::addObject(GameObject2D* object2D) {
	gameObjects.push_back(object2D);
}


void Graphics::Display::render() {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	for (std::vector<GameObject2D*>::iterator it = gameObjects.begin();
		       	it != gameObjects.end(); it++) {
		(*it)->render(gRenderer);
	}


	for (std::vector<GLabel*>::iterator it = labels.begin();
		       	it != labels.end(); it++) {
		tre->writeText((*it)->x, (*it)->y, (*it)->text);
	}
 

	SDL_RenderPresent(gRenderer);
}


SDL_Texture* Graphics::Display::loadTexture(std::string path) {
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
		printf("[Error] Unable to load surface: %s\n", SDL_GetError());
	else {
		return SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	}

	return NULL;
}


unsigned int Graphics::Display::getWidth() {
	return SCREEN_WIDTH;
}


unsigned int Graphics::Display::getHeight() {
	return SCREEN_HEIGHT;
}


Graphics::GLabel* Graphics::Display::createLabel(std::string text, int x, int y) {
	GLabel* l = new GLabel;
	l->x = x;
	l->y = y;
	l->text = text;
	labels.push_back(l);

	return l;
}
