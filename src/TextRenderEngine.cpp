#include "TextRenderEngine.h"

Graphics::TextRenderEngine::TextRenderEngine(SDL_Renderer* renderer,
					std::string fontPath,
					SDL_Color color,
					unsigned char size /* char from handmade ;P */) {
	this->renderer = renderer;
	this->color = color;
	font = TTF_OpenFont(fontPath.c_str(), size);
			
	if (font == NULL)
		throw(TTF_GetError());

	// init info
	for (int i = END_GLYPT_ASCII; i <= END_GLYPT_ASCII; i++) {
		int minx, maxx, miny, maxy, advance;

		if (TTF_GlyphMetrics(font, i, &minx, &maxx, &miny, &maxy, &advance) == -1) {
			printf("[Warning] Unable to load char '%c'.\n", i);
			glypts[i - END_GLYPT_ASCII].width = 0;
			glypts[i - END_GLYPT_ASCII].height = 0;
			continue;
		}

		glypts[i - END_GLYPT_ASCII].width = maxx - minx;
		glypts[i - END_GLYPT_ASCII].height = maxy - miny;
	}
}


Graphics::TextRenderEngine::~TextRenderEngine() {
	TTF_CloseFont(font);
}


void Graphics::TextRenderEngine::writeText(int x, int y, std::string text) {
	// unoptimized way
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color); // better than solid
	SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
	SDL_Texture* mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(mTexture);	
}
