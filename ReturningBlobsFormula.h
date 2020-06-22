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
		auto& blobs(lController->manager->getGroup(groupBlobsActive));

		for (auto& b : blobs)
		{
			if ((b->state == surviving || b->state == reproducing) && !(b->getComponent<DestinationComponent>().isActive()) && !(b->getComponent<DestinationComponent>().isReached()))
			{
				Point dest = calcClosestWall(b->getComponent<TransformComponent>().position.x,
												b->getComponent<TransformComponent>().position.y,
												b->getComponent<TransformComponent>().width, 
												b->getComponent<TransformComponent>().height);
				b->getComponent<RandomWalkComponent>().deactivate();
				b->getComponent<SightComponent>().deactivate();
				b->getComponent<DestinationComponent>().activate();
				b->getComponent<DestinationComponent>().setXY(dest.x, dest.y);
			}


			if ((b->state == surviving || b->state == reproducing) && b->getComponent<DestinationComponent>().isActive() && b->getComponent<DestinationComponent>().isReached())
			{
					b->getComponent<DestinationComponent>().deactivate();
					b->getComponent<SpriteComponent>().deactivate();
					b->getComponent<TransformComponent>().deactivate();
			}
			

		}

	}

	Point calcClosestWall(float X, float Y, float W, float H)
	{
		distDW = abs(DW - Y);
		distUW = abs(UW - Y);
		distLW = abs(LW - X);
		distRW = abs(RW - X);

		if (distDW == std::min({ distDW, distUW, distLW, distRW }))
		{
			return Point(X, DW - H / 2 - 2);
		}
		if (distUW == std::min({ distDW, distUW, distLW, distRW }))
		{
			return Point(X, UW + H / 2 + 2);
		}
		if (distLW == std::min({ distDW, distUW, distLW, distRW }))
		{
			return Point(LW + W / 2 + 2, Y);
		}
		if (distRW == std::min({ distDW, distUW, distLW, distRW }))
		{
			return Point(RW - W / 2 - 2, Y);
		}


	}

	float distRW, distLW, distUW, distDW;
	float RW, LW, UW, DW;

};