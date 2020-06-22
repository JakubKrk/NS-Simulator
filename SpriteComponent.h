#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Game.h"
#include "Animation.h"
#include <map>
#include <string>

class SpriteComponent : public Component
{
private:

	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	bool fullTexture = false;
	std::string filePath;
	int frames = 0;
	int speed = 0;

public:

	bool animated = false;
	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SpriteComponent() = default;
	SpriteComponent(std::string path)
	{
		filePath = path;
		const char* c = filePath.c_str();
		setTexture(c);
	}

	SpriteComponent(std::string path, bool isAnimated)
	{

		Animation Up = Animation(1, 2, 100);
		Animation Down = Animation(0, 2, 100);
		Animation Left = Animation(3, 2, 100);
		Animation Right = Animation(2, 2, 100);
		Animation Dead = Animation(4, 1, 100);
		Animation Eaten = Animation(5, 1, 100);

		animations.emplace("Up", Up);
		animations.emplace("Down", Down);
		animations.emplace("Left", Left);
		animations.emplace("Right", Right);
		animations.emplace("Dead", Dead);
		animations.emplace("Eaten", Eaten);

		filePath = path;
		const char* c = filePath.c_str();

		setTexture(c);
		animated = isAnimated;
		Play("Up");

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
		activate();
		srcRect.x = srcRect.y = 0;

		srcRect.w = transform->basewidth;
		srcRect.h = transform->baseheight;
		
		destRect.w = transform->width;
		destRect.h = transform->height;
	}

	void update() override
	{

		if (animated && isActive()){
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		if (!isActive()) {
			srcRect.x = 0;
		}
	
		srcRect.y = animIndex * transform->baseheight;
		

		destRect.x = int((transform->position.x)-((transform->width)/2));
		destRect.y = int((transform->position.y)-((transform->height)/2));
		destRect.w = int(transform->width);
		destRect.h = int(transform->height);
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

		if (!fullTexture) {
			TextureManager::Draw(texture, srcRect, destRect);
		}
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		speed = animations[animName].speed;
		animIndex = animations[animName].index;
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

};