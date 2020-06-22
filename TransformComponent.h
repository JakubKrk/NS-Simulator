#pragma once

#include "Components.h"
#include "Vector2D.h"
#include "Point.h"
#include "ECS.h"


class TransformComponent : public Component
{
public:

	Point position;
	Vector2D velocity;

	int height;
	int width;
	float scale;
	int baseheight;
	int basewidth;

	TransformComponent()
	{
		position.x = 0.0f;
		position.y = 0.0f;
		velocity.setAngle(0);
		baseheight = height = 32;
		basewidth = width = 32;
		scale = 1;
	}

	TransformComponent(float x, float y, int h, int w, float s)
	{
		position.x = x;
		position.y = y;
		baseheight = height = h;
		basewidth = width = w;
		scale = s;
		height = baseheight * scale;
		width = basewidth * scale;
	}


	void init() override
	{
		deactivate();
	}

	void update() override
	{
		if (isActive()) {
			position.x += velocity.X() * entity->speed;
			position.y += velocity.Y() * entity->speed;
			entity->energy -= (entity->speed)*2 + (entity->speed)* (entity->speed) + (entity->size)* (entity->size)* (entity->size);
		}
	}

	void setScale(float s)
	{
		scale = s;
		height = baseheight * scale;
		width = basewidth * scale;

	}

};