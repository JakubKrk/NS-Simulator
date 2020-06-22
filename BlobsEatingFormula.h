#pragma once
#include "LCS.h"
#include "Formulas.h"
#include <iostream>
#include "Collision.h"


struct BlobsEatingFormula : public Formula
{

	LogicController* lController;
	int agressioncounter;

	void init() override
	{
		agressioncounter = 0;
	}

	void update() override
	{



		//if ((Game::aggresion == false) && (agressioncounter < Game::blobsAressionDelay)) {
		//	agressioncounter++;
		//}

		//if ((Game::aggresion == false) && (agressioncounter == Game::blobsAressionDelay)) {
		//	Game::aggresion = true;
		//	agressioncounter = 0;
		//}

		if (Game::aggresion) {

			auto& blobs(lController->manager->getGroup(groupBlobsActive));

			for (auto& b1 : blobs)
			{
				if (b1->state == hunting) {

					for (auto& b2 : blobs)
					{
						if (b2->state == hunting) {

							if (b1->size > 1.25 * b2->size) {

								if (Collision::AABB(b1->getComponent<ColliderComponent>().collider,
									b2->getComponent<ColliderComponent>().collider))
								{
									b1->eaten += 1;

									b2->getComponent<TransformComponent>().deactivate();
									b2->getComponent<MovementSpriteChanger>().deactivate();
									b2->getComponent<RandomWalkComponent>().deactivate();
									b2->getComponent<SpriteComponent>().deactivate();
									b2->getComponent<DestinationComponent>().deactivate();
									b2->getComponent<SpriteComponent>().setColor(255, 128, 128);
									b2->getComponent<SpriteComponent>().Play("Eaten");
									b2->state = dead;

								}
							}
						}
					}

				}
			}
		}
		


	}



};