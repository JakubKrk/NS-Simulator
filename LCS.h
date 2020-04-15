#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "ECS.h"
#include "Components.h"
#include "Game.h"
#include "Board.h"
#include "Blob.h"
#include <random>

int random(int min, int max) {
	static std::random_device device{};
	static std::default_random_engine engine{ device() };
	std::uniform_int_distribution<int> distribution{ min, max };
	return distribution(engine);
}

class LogicController;
class Formula;

//class Board;

using FormulaID = std::size_t;

inline FormulaID getFormulaID()
{
	static FormulaID lastID = 0u;
	return lastID++;
}

template <typename T> inline FormulaID getFormulaID() noexcept
{
	static FormulaID typeID = getFormulaID();
	return typeID;
}

constexpr std::size_t maxFormulas = 32;

using FormulaArray = std::array<Formula*, maxFormulas>;


struct Formula
{

	LogicController* lController;

	virtual void init() {

	}
	virtual void update() {

	}
	virtual void draw() {

	}

	virtual ~Formula() {}

};

class LogicController
{
public:

	std::vector < std::unique_ptr<Formula>> formulas;

	FormulaArray formulasArray;
	Manager* manager = nullptr;

	LogicController(Manager* mManager)
	{
		manager = mManager;
	}

	void update()
	{
		for (auto& f : formulas) f->update();
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* f(new T(std::forward<TArgs>(mArgs)...));
		f->lController = this;
		std::unique_ptr<Formula> uPtr{ f };
		formulas.emplace_back(std::move(uPtr));

		formulasArray[getFormulaID<T>()] = f;

		f->init();
		return *f;

	}

	void CreateEnviroment()
	{
		auto grass(manager->addEntity<Entity>());
		auto upperwall(manager->addEntity<Entity>());
		auto lowerwall(manager->addEntity<Entity>());
		auto rightwall(manager->addEntity<Entity>());
		auto leftwall(manager->addEntity<Entity>());

		grass->addComponent<TransformComponent>(Game::board->X, Game::board->Y, Game::board->H, Game::board->W, 1);
		grass->addComponent<SpriteComponent>("assets/grasstexture.png");
		grass->addGroup(groupBackground);
		grass->getComponent<SpriteComponent>().setFullTexture(true);


		upperwall->addComponent<TransformComponent>(Game::board->X, Game::board->Y - (Game::board->H / 2) - 25, 50, Game::board->W, 1);
		upperwall->addComponent<ColliderComponent>("wallX");
		upperwall->addGroup(groupWallHorizontal);

		rightwall->addComponent<TransformComponent>(Game::board->X + (Game::board->W / 2) + 25, Game::board->Y, Game::board->H, 50, 1);
		rightwall->addComponent<ColliderComponent>("wallY");
		rightwall->addGroup(groupWallVertical);

		leftwall->addComponent<TransformComponent>(Game::board->X - (Game::board->W / 2) - 25, Game::board->Y, Game::board->H, 50, 1);
		leftwall->addComponent<ColliderComponent>("wallY");
		leftwall->addGroup(groupWallVertical);

		lowerwall->addComponent<TransformComponent>(Game::board->X, Game::board->Y + (Game::board->H / 2) + 25, 50, Game::board->W, 1);
		lowerwall->addComponent<ColliderComponent>("wallX");
		lowerwall->addGroup(groupWallHorizontal);

	}

	void SpawnFood(int food)
	{
		int coordinateX, coordinateY;

		for (int i = 0; i < food; i++) {
			auto* nFood(manager->addEntity<Food>());
			coordinateX = random(Game::board->X - Game::board->W / 2 + 50, Game::board->X + Game::board->W / 2 - 50);
			coordinateY = random(Game::board->Y - Game::board->H / 2 + 50, Game::board->Y + Game::board->H / 2 - 50);

			nFood->getComponent<TransformComponent>().position.x = coordinateX;
			nFood->getComponent<TransformComponent>().position.y = coordinateY;

		}

	}


	void SpawnBlobs(int blobs)
			{
				std::srand(std::time(nullptr));
				int wall;
				int coordinate;
		
				for (int i = 0; i < blobs; i++) {
					wall = rand() % 4;
					auto* nBlob(manager->addEntity<Blob>());
					switch (wall)
					{
					case 0: //lower wall
						coordinate = rand() % ((Game::board->W)-100) + 100;
						nBlob->getComponent<TransformComponent>().position.x = coordinate;
						nBlob->getComponent<TransformComponent>().position.y = Game::board->Y + (Game::board->H / 2) - 16;
						nBlob->getComponent<TransformComponent>().velocity.setAngle(270);
						break;
		
					case 1: //upper wall
						coordinate = rand() % ((Game::board->W) - 100) + 100;
						nBlob->getComponent<TransformComponent>().position.x = coordinate;
						nBlob->getComponent<TransformComponent>().position.y = Game::board->Y - (Game::board->H / 2) + 16;
						nBlob->getComponent<TransformComponent>().velocity.setAngle(90);
						break;
		
					case 2: //right wall
						coordinate = rand() % ((Game::board->H) - 100) + 100;
						nBlob->getComponent<TransformComponent>().position.x = Game::board->X + (Game::board->W / 2) - 16;
						nBlob->getComponent<TransformComponent>().position.y = coordinate;
						nBlob->getComponent<TransformComponent>().velocity.setAngle(180);
						break;
		
					case 3: //left wall
						coordinate = rand() % ((Game::board->H) - 100) + 100;
						nBlob->getComponent<TransformComponent>().position.x = Game::board->X - (Game::board->W / 2) + 16;
						nBlob->getComponent<TransformComponent>().position.y = coordinate;
						nBlob->getComponent<TransformComponent>().velocity.setAngle(0);
						break;
		
					default:
						break;
					}
		
		
					for (auto& e : manager->getGroup(groupBlobsActive)) e->getComponent<MovementSpriteChanger>().update();

				}
			}

};