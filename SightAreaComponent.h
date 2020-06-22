#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Game.h"
#include <string>

class SightAreaComponent : public Component
{
private:

	TransformComponent* transform;
	SightComponent* sighter;

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	bool fullTexture = true;
	std::string filePath;

public:


	SightAreaComponent() = default;
	SightAreaComponent(std::string path)
	{
		filePath = path;
		const char* c = filePath.c_str();
		setTexture(c);
	}


	void setFullTexture(bool c)
	{
		fullTexture = c;
	}

	void setTexture(const char* path)
	{
		SDL_DestroyTexture(texture);
		texture = TextureManager::LoadTexture(path);
	}

	void updateTexture()
	{
		const char* c = filePath.c_str();
		SDL_DestroyTexture(texture);
		texture = TextureManager::LoadTexture(c);

	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sighter = &entity->getComponent<SightComponent>();
		activate();
		destRect.w = int(2 * sighter->sight.r);
		destRect.h = int(2 * sighter->sight.r);

		destRect.x = int(transform->position.x - sighter->sight.r);
		destRect.y = int(transform->position.y - sighter->sight.r);
	}

	void update() override
	{
		destRect.w = int(2 * sighter->sight.r);
		destRect.h = int(2 * sighter->sight.r);

		destRect.x = int(transform->position.x - sighter->sight.r);
		destRect.y = int(transform->position.y - sighter->sight.r);
	}

	void setColor(Uint8 red, Uint8 green, Uint8 blue)
	{
		SDL_SetTextureColorMod(texture, red, green, blue);
	}

	void draw() noexcept override
	{
		if (fullTexture) {
			TextureManager::DrawFull(texture, destRect);
		}
	}

	~SightAreaComponent()
	{
		SDL_DestroyTexture(texture);
	}

};