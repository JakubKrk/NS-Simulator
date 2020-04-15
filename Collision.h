#pragma once
#include "SDL.h"
#include <memory>

class ColliderComponent;
class Entity;

class Collision
{
public:
	static bool AABB(const SDL_Rect recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool AABB(const Entity* entA, const Entity* entB);
	static bool AABB(const std::unique_ptr<Entity> entA, const std::unique_ptr<Entity> entB);
};