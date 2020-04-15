#pragma once
#include "LCS.h"
#include "Formulas.h"
#include <iostream>
#include "Collision.h"


struct WallCollisionFormula : public Formula
{

	LogicController* lController;

	void init() override
	{
		
	}

	void update() override
	{

		auto blobs(lController->manager->getGroup(groupBlobsActive));
		auto wallsV(lController->manager->getGroup(groupWallVertical));
		auto wallsH(lController->manager->getGroup(groupWallHorizontal));


		for (auto& b : blobs)
		{

			for (auto& wv : wallsV)
			{
				if (Collision::AABB(b, wv))
				{
					b->getComponent<TransformComponent>().velocity.inverseX();
					//b->getComponent<TransformComponent>().position.x = b->getComponent<TransformComponent>().position.x + 4 * (-b->getComponent<TransformComponent>().velocity.X());

				}

			}
		}

		for (auto& b : blobs)
		{
			for (auto& wh : wallsH)
			{
				if (Collision::AABB(b, wh))
				{

					b->getComponent<TransformComponent>().velocity.inverseY();
					//b->getComponent<TransformComponent>().position.y = b->getComponent<TransformComponent>().position.y + 4 * (-b->getComponent<TransformComponent>().velocity.Y());

				}

			}
		}



	}


};