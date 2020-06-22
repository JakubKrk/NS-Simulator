#pragma once
#include "LCS.h"
#include "Formulas.h"

struct OutOfBoardFormula : public Formula
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

				if ((b->getComponent<TransformComponent>().position.x >= (Game::board->X+(Game::board->W/2))) ||
					(b->getComponent<TransformComponent>().position.x <= (Game::board->X - (Game::board->W / 2))) ||
						(b->getComponent<TransformComponent>().position.y >= (Game::board->Y + (Game::board->H / 2))) ||
							(b->getComponent<TransformComponent>().position.y <= (Game::board->Y - (Game::board->H / 2))))
				{
					b->getComponent<TransformComponent>().position.x = Game::board->X;
					b->getComponent<TransformComponent>().position.y = Game::board->Y;
				}

		}

	}


};