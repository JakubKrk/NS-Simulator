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

		auto blobs(lController->manager->getGroup(groupBlobsActive));
		auto food(lController->manager->getGroup(groupFood));

		for (auto& b : blobs)
		{

			for (auto& f : food)
			{
				if (Collision::AABB(b, f))
				{
					if (b->eaten < 2) {
						b->eaten += 1;
						f->destroy();
					}
				}

			}
		}
	}


};