#pragma once
#include "Game.h"

class TextureManager
{
public:

	static SDL_Texture* LoadTexture(const char* filename)
	{
		SDL_Surface* tmpSurface = IMG_Load(filename);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
		return texture;
	}

	static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
		SDL_RenderCopy(Game::renderer, texture, &src, &dest);
	}

	static void DrawFull(SDL_Texture* texture, SDL_Rect dest) {
		SDL_RenderCopy(Game::renderer, texture, NULL, &dest);
	}

};

