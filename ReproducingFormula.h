#pragma once
#include "LCS.h"
#include "Formulas.h"
#include <algorithm>

struct ReproducingFormula : public Formula
{

	LogicController* lController;
	int wcounter = 0;
	int wcounteriters = 20;
	bool firstiter = true;


	void init() override
	{

	}

	void update() override
	{

		if (Game::state == greproducing)
		{
			auto& blobs(lController->manager->getGroup(groupBlobsActive));

			if (firstiter) {


				for (auto& b : blobs) {


					if (b->state == reproducing) {
						lController->ReproduceBlob(b.get());
					}
				}
				firstiter = false;

			}
			if (wcounter < wcounteriters) {
				wcounter++;
			}

			if (wcounter == wcounteriters) {


				for (auto& b : blobs)
				{
					b->energy = Game::startingEnergy;
					b->state = hunting;
					b->eaten = 0;
					b->getComponent<TransformComponent>().activate();
					b->getComponent<RandomWalkComponent>().activate();
					b->getComponent<SpriteComponent>().activate();
					b->getComponent<SightComponent>().activate();
				}

				lController->SpawnFood(Game::foodForGeneration);
				Game::state = ghunting;
				firstiter = true;
				wcounter = 0;
			}
		}



	}

	
};