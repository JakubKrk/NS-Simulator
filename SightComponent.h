#pragma once
#include "Components.h"
#include "ECS.h"
#include "SDL.h"

struct Circle
{
	int x = 0;
	int	y = 0;
	int r = 0;
};

class SightComponent : public Component
{
public:

	Circle sight;
	std::string tag;

	TransformComponent* transform;

	SightComponent()
	{
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{

		sight.x = transform->position.x;
		sight.y = transform->position.y;
		sight.r = entity->sight*35;

	}

};