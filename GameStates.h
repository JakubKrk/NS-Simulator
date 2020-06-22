#pragma once
#include "LCS.h"
#include "Formulas.h"
#include "Game.h"

struct GameStatesFormula : public Formula
{

	LogicController* lController;
	bool outofenergy = false;
	int wcounter = 0;
	int wcounteriters = 20;
	int agressioncounter = 0;

	GameStatesFormula()
	{
	}

	void init() override
	{

	}

	void update() override
	{
		auto& blobs(lController->manager->getGroup(groupBlobsActive));


		if (Game::state == ghunting) {
			bool none = true;

			if (wcounter < wcounteriters)
			{
				wcounter++;
			}
			if (wcounter >= wcounteriters)
			{

				if ((Game::aggresion == false) && (agressioncounter < Game::blobsAressionDelay)) {
					agressioncounter++;
				}

				if ((Game::aggresion == false) && (agressioncounter == Game::blobsAressionDelay)) {
					Game::aggresion = true;
					std::cout << "AGRRO ON" << std::endl;
					agressioncounter = 0;
				}

				for (auto& b : blobs)
				{
					if (b->state == hunting)
					{
						none = false;
						break;
					}
				}

				if (none) {
					Game::state = greturning;
					Game::aggresion = false;
					wcounter = 0;
					return;
				}


			}
		}


		if (Game::state == greturning) {
			bool none = true;

			for (auto& b : blobs)
			{
				if (b->getComponent<DestinationComponent>().isActive())
				{
					none = false;
					break;
				}
			}

			if (none) {
				Game::state = gwaiting;
				return;
			}
		}

		if (Game::state == gwaiting) {

			if (wcounter < wcounteriters)
			{
				wcounter++;
			}
			if (wcounter >= wcounteriters)
			{
				auto& food(lController->manager->getGroup(groupFood));

				for (auto& f : food)
				{
					f->destroy();
				}

				for (auto& b : blobs)
				{
					if (b->state == dead)
					{
						b->destroy();
						continue;
					}
					else {
						if ((abs(b->getComponent<TransformComponent>().velocity.A() - 0) < 15) || (abs(b->getComponent<TransformComponent>().velocity.A() - 360) < 15)) {
							b->getComponent<TransformComponent>().velocity.setAngle(180);
							continue;
						}

						if (abs(b->getComponent<TransformComponent>().velocity.A() - 180) < 15) {
							b->getComponent<TransformComponent>().velocity.setAngle(0);
							continue;
						}

						if (abs(b->getComponent<TransformComponent>().velocity.A() - 90) < 15) {
							b->getComponent<TransformComponent>().velocity.setAngle(270);
							continue;
						}

						if (abs(b->getComponent<TransformComponent>().velocity.A() - 270) < 15) {
							b->getComponent<TransformComponent>().velocity.setAngle(90);
							continue;
						}
					}

				}
				wcounter = 0;
				Game::state = greproducing;
				Game::generation++;
				std::cout << Game::generation << std::endl;
			}
		}


		if (Game::state == greproducing) {
			bool none = true;

			for (auto& b : blobs)
			{
				if (b->state != hunting)
				{
					none = false;
					break;
				}
			}

			if (none) {
				Game::state = ghunting;

				return;
			}

		}

		if (Game::state != generationspassed) {
			if (Game::generation == Game::lastGeneration) {
				Game::state = generationspassed;
				//lController->LoadGraphs();
				lController->update();
			}
		}
	}

};