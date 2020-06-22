#pragma once
#include "SDL.h"
#include <memory>

class ColliderComponent;
class SightComponent;
class Entity;

struct Circle;

class Collision
{
public:

	//rect x rect
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool AABB(const Entity* entA, const Entity* entB);
	static bool AABB(const std::unique_ptr<Entity> entA, const std::unique_ptr<Entity> entB);


	// circle x circle
	static bool RR(const Circle& cirA, const Circle& cirB);
	static bool RR(const SightComponent& sigA, const SightComponent& sigB);
	static bool RR(const Entity* entA, const Entity* entB);
	static bool RR(const std::unique_ptr<Entity> entA, const std::unique_ptr<Entity> entB);


	// circle x rect
	static bool RBB(const Circle& cirA, const SDL_Rect& recB);
	static bool RBB(const SightComponent& sigA, const ColliderComponent& recB);
	static bool RBB(const Entity* entA, const Entity* entB);
	static bool RBB(const std::unique_ptr<Entity> entA, const std::unique_ptr<Entity> entB);

};