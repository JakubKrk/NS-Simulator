#include "Collision.h"
#include "ColliderComponent.h"

double distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		)
	{
		return true;
	}

	return false;
}

bool  Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{

	if (AABB(colA.collider, colB.collider))
	{
		return true;


	}
	else
	{
		return false;
	}
}

bool Collision::AABB(const Entity* entA, const Entity* entB)
{
	
	return AABB(entA->getComponent<ColliderComponent>(), entB->getComponent<ColliderComponent>());
}

bool Collision::AABB(const std::unique_ptr<Entity> entA, const std::unique_ptr<Entity> entB)
{
	return AABB(entA->getComponent<ColliderComponent>(), entB->getComponent<ColliderComponent>());
}

bool Collision::RR(const Circle& cirA,const Circle& cirB){

	//Calculate total radius squared
	int totalRadiusSquared = cirA.r + cirB.r;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

	if (distanceSquared(cirA.x, cirA.y, cirB.x, cirB.y) < (totalRadiusSquared))
	{
		return true;
	}

	return false;
}

bool  Collision::RR(const SightComponent& sigA, const SightComponent& sigB)
{

	if (RR(sigA.sight, sigB.sight))
	{
		return true;

	}
	else
	{
		return false;
	}
}

bool Collision::RR(const Entity* entA, const Entity* entB)
{

	return RR(entA->getComponent<SightComponent>(), entB->getComponent<SightComponent>());
}

bool Collision::RR(const std::unique_ptr<Entity> entA, const std::unique_ptr<Entity> entB)
{
	return RR(entA->getComponent<SightComponent>(), entB->getComponent<SightComponent>());
}



bool Collision::RBB(const Circle& cirA, const SDL_Rect& recB) {

	int cX, cY;

	if (cirA.x < recB.x)
	{
		cX = recB.x;
	}
	else if (cirA.x > recB.x + recB.w)
	{
		cX = recB.x + recB.w;
	}
	else
	{
		cX = cirA.x;
	}

	if (cirA.y < recB.y)
	{
		cY = recB.y;
	}
	else if (cirA.y > recB.y + recB.h)
	{
		cY = recB.y + recB.h;
	}
	else
	{
		cY = cirA.y;
	}

	if (distanceSquared(cirA.x, cirA.y, cX, cY) < cirA.r * cirA.r)
	{
		return true;
	}

	return false;

}

bool  Collision::RBB(const SightComponent& sigA, const ColliderComponent& recB)
{

	if (RBB(sigA.sight, recB.collider))
	{
		return true;


	}
	else
	{
		return false;
	}
}

bool Collision::RBB(const Entity* entA, const Entity* entB)
{

	return RBB(entA->getComponent<SightComponent>(), entB->getComponent<ColliderComponent>());
}

bool Collision::RBB(const std::unique_ptr<Entity> entA, const std::unique_ptr<Entity> entB)
{
	return RBB(entA->getComponent<SightComponent>(), entB->getComponent<ColliderComponent>());
}