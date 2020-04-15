#pragma once
#include "LCS.h"
#include "Formulas.h"


struct EnergyFormula : public Formula
{

	LogicController* lController;

	void init() override
	{

	}

	void update() override
	{
		auto blobs(lController->manager->getGroup(groupBlobsActive));

		for (auto b : blobs)
		{

			if (b->energy <= 0)
				{
				b->getComponent<TransformComponent>().deactivate();
				b->getComponent<MovementSpriteChanger>().deactivate();
				b->getComponent<RandomWalkComponent>().deactivate();
				b->getComponent<SpriteComponent>().deactivate();
				b->getComponent<SpriteComponent>().setColor(255, 128, 128);
				b->getComponent<SpriteComponent>().Play("Dead");
				b->addGroup(groupBlobsInactive);
				b->delGroup(groupBlobsActive);
				}

		}

	}


};