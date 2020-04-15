#pragma once
#include "ECS.h"
#include "Components.h"

class MovementSpriteChanger : public Component
{
public:

	SpriteComponent* sprite;
	TransformComponent* transform;

	MovementSpriteChanger(){}

	void init() override
	{
		sprite = &entity->getComponent<SpriteComponent>();
		transform = &entity->getComponent<TransformComponent>();
		activate();
	}
	

	void update() override
	{
		if (isActive())
		{
			if ( (transform->velocity.A() > 225) && (transform->velocity.A() <= 315))
			{
				sprite->Play("Up");
			}

			if ( (transform->velocity.A() > 135) && (transform->velocity.A() <= 225))
			{
				sprite->Play("Left");
			}

			if ( (transform->velocity.A() > 45) && (transform->velocity.A() <= 135))
			{
				sprite->Play("Down");
			}

			if ( ((transform->velocity.A() > 315) || (transform->velocity.A() <= 45)))
			{
				sprite->Play("Right");
			}
		}
	}
};