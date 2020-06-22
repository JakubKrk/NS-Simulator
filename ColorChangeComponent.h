#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Game.h"


class ColorChangeComponent : public Component
{
private:

	Uint8 red;
	Uint8 green;
	Uint8 blue;

	SpriteComponent* sprite;

public:



	ColorChangeComponent() = default;
	

	void init() override
	{
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		
	}

	void updateColor() {
		calcColor();
		sprite->setColor(red, green, blue);
	}

	void calcColor()
	{
		if (entity->speed >= 1) {
			blue = 128 + (entity->speed - 1) * 64;
		}
		if (entity->speed < 1) {
			blue = 128 - (1 - entity->speed) * 192;
		}
		if (entity->sight >= 1) {
			green = 128 + (entity->sight - 1) * 64;
		}
		if (entity->sight < 1) {
			green = 128 - (1 - entity->sight) * 192;
		}

		if (entity->size >= 1) {
			red = 128 + (entity->size - 1) * 64;
		}
		if (entity->size < 1) {
			red = 128 - (1 - entity->size) * 192;
		}	
	}

	~ColorChangeComponent()
	{
	}

};