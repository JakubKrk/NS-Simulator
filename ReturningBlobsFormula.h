#pragma once
#include "LCS.h"
#include "Formulas.h"
#include <iostream>
#include "Collision.h"
#include <algorithm>

struct ReturningBlobsFormula : public Formula
{

	LogicController* lController;
	Board* board;
	bool outofenergy = false;

	ReturningBlobsFormula()
	{
		board = Game::board;
	}

	void init() override
	{
		RW = board->X + (board->W / 2);
		LW = board->X - (board->W / 2);
		UW = board->Y - (board->H / 2);
		DW = board->Y + (board->H / 2);
	}

	void update() override
	{
		auto blobs(lController->manager->getGroup(groupBlobsActive));

		for (auto b : blobs)
		{
			if (b->eaten >= 2)
			{
				Point dest = calcClosestWall(b);
				b->getComponent<RandomWalkComponent>().deactivate();
				b->addComponent<DestinationComponent>();
				b->getComponent<DestinationComponent>().setXY(dest.x, dest.y);
				b->getComponent<SpriteComponent>().setColor(128, 128, 255);
			}

			if (b->hasComponent<DestinationComponent>())
			{
				if (b->getComponent<DestinationComponent>().isReached())
				{
					b->addComponent<DestinationComponent>().deactivate();
					b->getComponent<SpriteComponent>().setColor(128, 128, 128);
					b->getComponent<SpriteComponent>().deactivate();
				}
			}

		}

	}

	Point calcClosestWall(Entity* e)
	{
		distDW = abs(DW - e->getComponent<TransformComponent>().position.y);
		distUW = abs(UW - e->getComponent<TransformComponent>().position.y);
		distLW = abs(LW - e->getComponent<TransformComponent>().position.x);
		distRW = abs(RW - e->getComponent<TransformComponent>().position.x);

		if (distDW == std::min({ distDW, distUW, distLW, distRW }))
		{
			return Point(e->getComponent<TransformComponent>().position.x, DW - e->getComponent<TransformComponent>().height / 2 - 2);
		}
		if (distUW == std::min({ distDW, distUW, distLW, distRW }))
		{
			return Point(e->getComponent<TransformComponent>().position.x, UW + e->getComponent<TransformComponent>().height / 2 + 2);
		}
		if (distLW == std::min({ distDW, distUW, distLW, distRW }))
		{
			return Point(LW + e->getComponent<TransformComponent>().width / 2 + 2, e->getComponent<TransformComponent>().position.y);
		}
		if (distRW == std::min({ distDW, distUW, distLW, distRW }))
		{
			return Point(RW - e->getComponent<TransformComponent>().width / 2 - 2, e->getComponent<TransformComponent>().position.y);
		}


	}

	float distRW, distLW, distUW, distDW;
	float RW, LW, UW, DW;

};