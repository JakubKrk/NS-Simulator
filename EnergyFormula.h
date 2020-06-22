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
		auto& blobs(lController->manager->getGroup(groupBlobsActive));

		for (auto& b : blobs)
		{
			if (b->state == hunting) {
				if (b->energy <= 0)
				{
					if (b->eaten == 0) {
						b->getComponent<TransformComponent>().deactivate();
						b->getComponent<MovementSpriteChanger>().deactivate();
						b->getComponent<RandomWalkComponent>().deactivate();
						b->getComponent<DestinationComponent>().deactivate();
						b->getComponent<SpriteComponent>().deactivate();
						b->getComponent<ColorChangeComponent>().deactivate();
						b->getComponent<SpriteComponent>().setColor(255, 128, 128);
						b->getComponent<SpriteComponent>().Play("Dead");
						b->state = dead;
					}
					if (b->eaten == 1) {
						b->state = surviving;
						b->getComponent<DestinationComponent>().deactivate();
					}
				}
				if (b->eaten >= 2) {
					b->state = reproducing;
					b->getComponent<DestinationComponent>().deactivate();
				}
			}

		}

	}


};