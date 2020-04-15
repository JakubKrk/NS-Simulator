#pragma once

#pragma once

#include "Components.h"
#include "Animation.h"
#include <map>



class DestinationComponent : public Component
{
private:

	Point destination;
	Vector2D velocity;
	float dX, dY;

	TransformComponent* transform;

public:

	DestinationComponent() {}

	void setXY(float mX, float mY)
	{
		destination.x = mX;
		destination.y = mY;
	}

	void calc()
	{
		dX = destination.x - transform->position.x;
		dY = destination.y - transform->position.y;
		velocity.setXY(dX, dY);
	}


	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		activate();
	}

	void update() override
	{
		if (isActive())
		{
			calc();
			if (sqrt(dX * dX + dY * dY) > transform->speed) {
				transform->velocity.setAngle(velocity.A());
			}
			if (sqrt(dX * dX + dY * dY) <= transform->speed) {
				transform->speed = 0;
				transform->position.x = destination.x;
				transform->position.y = destination.y;
			}

		}

	}

	bool isReached()
	{
		if (
			transform->position.x == destination.x &&
			transform->position.y == destination.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};



