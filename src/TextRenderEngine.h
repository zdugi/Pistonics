#ifndef TEXTRENDERENGINE_H
#define TEXTRENDERENGINE_H

#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>

namespace Graphics {
	
	const int START_GLYPT_ASCII = 33;
	const int END_GLYPT_ASCII = 126;	
	const int NUMBER_OF_CHARACTERS = 93; // 33 to 126
	
	struct GlyptInfo {
		short width;
		short height;
	};

	class TextRenderEngine {
		public:
			TextRenderEngine(SDL_Renderer* renderer,
					std::string fontPath,
					SDL_Color color,
					unsigned char size /* char from handmade ;P */);
			~TextRenderEngine();

			 void writeText(int x, int y, std::string text);
		private:
			TTF_Font *font;
			SDL_Color color;
			SDL_Renderer* renderer;
			GlyptInfo glypts[NUMBER_OF_CHARACTERS];
	};
}

#endif
