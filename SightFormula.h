#pragma once
#include "LCS.h"
#include "Formulas.h"
#include <iostream>
#include "Collision.h"


struct SightFormula : public Formula
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
			if (b->state==hunting){

				if (b->getComponent<SightComponent>().isActive()) {

					bool chasingfood = false;
					bool chasingblob = false;
					bool runningaway = false;

					//run from bigger blob

					for (auto& b2 : blobs)
					{
						if (b2->state == hunting) {
							if (Collision::RBB(b->getComponent<SightComponent>().sight,
								b2->getComponent<ColliderComponent>().collider))
							{
								if (b2->size > 1.25 * b->size) {
									b->getComponent<RandomWalkComponent>().deactivate();

									b->getComponent<DestinationComponent>().activate();

									float x, y;
									float dX, dY;

									dX = b2->getComponent<TransformComponent>().position.x - b->getComponent<TransformComponent>().position.x;
									if (dX >= 0) {
										x = b->getComponent<TransformComponent>().position.x - 10;
									}
									if (dX < 0) {
										x = b->getComponent<TransformComponent>().position.x + 10;
									}

									dY = b2->getComponent<TransformComponent>().position.y - b->getComponent<TransformComponent>().position.y;
									if (dY >= 0) {
										y = b->getComponent<TransformComponent>().position.y - 10;
									}
									if (dY < 0) {
										y = b->getComponent<TransformComponent>().position.y + 10;
									}

									b->getComponent<DestinationComponent>().setXY(x, y);
									runningaway = true;
									break;
								}
							}
						}
					}
				

					//chase food
					if (!runningaway){
						for (auto& f : food)
						{
							if (f->isActive()) {
								if (Collision::RBB(b->getComponent<SightComponent>().sight,
									f->getComponent<ColliderComponent>().collider))
								{
									b->getComponent<RandomWalkComponent>().deactivate();
									b->getComponent<DestinationComponent>().activate();
									b->getComponent<DestinationComponent>().setXY(f->getComponent<TransformComponent>().position.x, f->getComponent<TransformComponent>().position.y);
									chasingfood = true;
									break;
								}
							}
						}
					}

					//chase smaller blob
					if (!chasingfood && !runningaway && Game::aggresion) {
						for (auto& b2 : blobs)
						{
							if (b2->state == hunting) {
								if (Collision::RBB(b->getComponent<SightComponent>().sight,
									b2->getComponent<ColliderComponent>().collider))
								{
									if (b->size > 1.25 * b2->size) {
										b->getComponent<RandomWalkComponent>().deactivate();

										b->getComponent<DestinationComponent>().activate();
										b->getComponent<DestinationComponent>().setXY(b2->getComponent<TransformComponent>().position.x, b2->getComponent<TransformComponent>().position.y);
										chasingblob = true;
										break;
									}
								}
							}
						}
					}

					if (!chasingfood && !chasingblob && !runningaway) {
						b->getComponent<RandomWalkComponent>().activate();
						b->getComponent<DestinationComponent>().deactivate();
					}
				}
			}
		}

	}


};