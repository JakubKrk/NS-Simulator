#pragma once
#include "LCS.h"
#include "Formulas.h"
#include <iostream>
#include "Collision.h"


struct FoodEatingFormula : public Formula
{

	LogicController* lController;

	void init() override
	{

	}

	void update() override
	{

		auto& blobs(lController->manager->getGroup(groupBlobsActive));
		auto& food(lController->manager->getGroup(groupFood));

		for (auto& b : blobs)
		{
			if (b->state == hunting) {

				for (auto& f : food)
				{
					if (f->isActive()) {

						if (Collision::AABB(b->getComponent<ColliderComponent>().collider,
							f->getComponent<ColliderComponent>().collider))
						{
							b->eaten += 1;
							f->destroy();
						
						}
					}
				}

			}
		}


	}



};