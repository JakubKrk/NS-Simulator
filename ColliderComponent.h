#pragma once
#include "Components.h"
#include "ECS.h"
#include "SDL.h"

class ColliderComponent : public Component
{	
public:

	SDL_Rect collider;
	std::string tag;

	TransformComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		//Game::colliders.push_back(this);
	}

	void update() override
	{

		collider.x = static_cast<int>(transform->position.x - ((transform->width) / 2));
		collider.y = static_cast<int>(transform->position.y - ((transform->height) / 2));
		collider.h = transform->height;
		collider.w = transform->width;

	}

};