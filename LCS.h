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
	unsigned seed;
	std::default_random_engine e;


	LogicController(Manager* mManager)
	{
		manager = mManager;
		seed = std::chrono::steady_clock::now().time_since_epoch().count();
		std::default_random_engine e(seed);
	}

	void update()
	{
		for (auto& f : formulas) {
			f->update();
			manager->refresh();
		}
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

	template <typename T> T& getComponent() const
	{
		auto ptr(formulasArray[getFormulaID<T>()]);
		return *static_cast <T*>(ptr);
	}

	float calcRandom(float mean, float dev, float min, float max) {

		std::normal_distribution<double> distribution(mean, dev*mean);
		float nValue = distribution(e);
		if (nValue < min) {
			nValue = min;
		}
		if (nValue > max) {
			nValue = max;
		}
		return nValue;
	}


	void SpawnEnviroment()
	{
		auto grass(manager->addEntity<Entity>(groupBackground));
		auto upperwall(manager->addEntity<Entity>(groupWallHorizontal));
		auto lowerwall(manager->addEntity<Entity>(groupWallHorizontal));
		auto rightwall(manager->addEntity<Entity>(groupWallVertical));
		auto leftwall(manager->addEntity<Entity>(groupWallVertical));

		grass->addComponent<TransformComponent>(Game::board->X, Game::board->Y, Game::board->H, Game::board->W, 1);
		grass->addComponent<SpriteComponent>("assets/grasstexture.png");
		grass->getComponent<SpriteComponent>().setFullTexture(true);


		upperwall->addComponent<TransformComponent>(Game::board->X, Game::board->Y - (Game::board->H / 2) - 25, 50, Game::board->W, 1);
		upperwall->addComponent<ColliderComponent>("wallX");

		rightwall->addComponent<TransformComponent>(Game::board->X + (Game::board->W / 2) + 25, Game::board->Y, Game::board->H, 50, 1);
		rightwall->addComponent<ColliderComponent>("wallY");

		leftwall->addComponent<TransformComponent>(Game::board->X - (Game::board->W / 2) - 25, Game::board->Y, Game::board->H, 50, 1);
		leftwall->addComponent<ColliderComponent>("wallY");

		lowerwall->addComponent<TransformComponent>(Game::board->X, Game::board->Y + (Game::board->H / 2) + 25, 50, Game::board->W, 1);
		lowerwall->addComponent<ColliderComponent>("wallX");

	}

	void LoadGraphs()
	{
		auto graph(manager->addEntity<Entity>(groupPlots));

		float width = 500;
		float height = 300;

		graph->addComponent<TransformComponent>(1280, 200, height, width, 1);

		graph->addComponent<SpriteComponent>("populations.png");
		//graph->getComponent<TransformComponent>().setScale(1);
		graph->getComponent<SpriteComponent>().setFullTexture(true);
	}

	void SpawnFood(int food)
	{
		int coordinateX, coordinateY;

		for (int i = 0; i < food; i++) {
			auto* nFood(manager->addEntity<Food>(groupFood));
			coordinateX = random(Game::board->X - Game::board->W / 2 + 50, Game::board->X + Game::board->W / 2 - 50);
			coordinateY = random(Game::board->Y - Game::board->H / 2 + 50, Game::board->Y + Game::board->H / 2 - 50);

			nFood->getComponent<TransformComponent>().position.x = coordinateX;
			nFood->getComponent<TransformComponent>().position.y = coordinateY;

		}

	}


	void SpawnBlobs(int blobs)
			{
				//std::srand(std::time(0));
				int wall;
				int coordinate;
		
				for (int i = 0; i < blobs; i++) {
					wall = rand() % 4;
					auto* nBlob(manager->addEntity<Blob>(groupBlobsActive));
					switch (wall)
					{
					case 0: //lower wall
						coordinate = rand() % ((Game::board->W)-100) + 100;
						nBlob->getComponent<TransformComponent>().position.x = coordinate;
						nBlob->getComponent<TransformComponent>().position.y = Game::board->Y + (Game::board->H / 2) - 16 * nBlob->size;
						nBlob->getComponent<TransformComponent>().velocity.setAngle(270);
						nBlob->getComponent<MovementSpriteChanger>().update();
						break;
		
					case 1: //upper wall
						coordinate = rand() % ((Game::board->W) - 100) + 100;
						nBlob->getComponent<TransformComponent>().position.x = coordinate;
						nBlob->getComponent<TransformComponent>().position.y = Game::board->Y - (Game::board->H / 2) + 16 * nBlob->size;
						nBlob->getComponent<TransformComponent>().velocity.setAngle(90);
						nBlob->getComponent<MovementSpriteChanger>().update();
						break;
		
					case 2: //right wall
						coordinate = rand() % ((Game::board->H) - 100) + 100;
						nBlob->getComponent<TransformComponent>().position.x = Game::board->X + (Game::board->W / 2) - 16 * nBlob->size;
						nBlob->getComponent<TransformComponent>().position.y = coordinate;
						nBlob->getComponent<TransformComponent>().velocity.setAngle(180);
						nBlob->getComponent<MovementSpriteChanger>().update();
						break;
		
					case 3: //left wall
						coordinate = rand() % ((Game::board->H) - 100) + 100;
						nBlob->getComponent<TransformComponent>().position.x = Game::board->X - (Game::board->W / 2) + 16 * nBlob->size;
						nBlob->getComponent<TransformComponent>().position.y = coordinate;
						nBlob->getComponent<TransformComponent>().velocity.setAngle(0);
						nBlob->getComponent<MovementSpriteChanger>().update();
						break;
		
					default:
						break;
					}
		
				}
			}

	void ReproduceBlob(Entity* parent) {

		auto* nBlob(manager->addEntity<Blob>(groupBlobsActive));

		nBlob->speed = calcRandom(parent->speed, Game::inhertianceDeviation, 0.33, 3.0);
		nBlob->size = calcRandom(parent->size, Game::inhertianceDeviation, 0.33, 3);
		nBlob->sight = calcRandom(parent->sight, Game::inhertianceDeviation, 0.33, 3);
		nBlob->getComponent<TransformComponent>().setScale(nBlob->size*0.25);

		switch (static_cast<int>(parent->getComponent<TransformComponent>().velocity.A()))
		{
		case 0:

			nBlob->getComponent<TransformComponent>().position.x = parent->getComponent<TransformComponent>().position.x + 10;
			nBlob->getComponent<TransformComponent>().position.y = parent->getComponent<TransformComponent>().position.y - 20;
			nBlob->getComponent<TransformComponent>().velocity.setAngle(0);
			break;

		case 90:

			nBlob->getComponent<TransformComponent>().position.x = parent->getComponent<TransformComponent>().position.x - 20;
			nBlob->getComponent<TransformComponent>().position.y = parent->getComponent<TransformComponent>().position.y + 10;
			nBlob->getComponent<TransformComponent>().velocity.setAngle(90);
			break;

		case 180:

			nBlob->getComponent<TransformComponent>().position.x = parent->getComponent<TransformComponent>().position.x - 10;
			nBlob->getComponent<TransformComponent>().position.y = parent->getComponent<TransformComponent>().position.y + 20;
			nBlob->getComponent<TransformComponent>().velocity.setAngle(180);
			break;

		case 270:

			nBlob->getComponent<TransformComponent>().position.x = parent->getComponent<TransformComponent>().position.x + 20;
			nBlob->getComponent<TransformComponent>().position.y = parent->getComponent<TransformComponent>().position.y - 10;
			nBlob->getComponent<TransformComponent>().velocity.setAngle(270);
			break;

		}

		nBlob->getComponent<MovementSpriteChanger>().update();
		nBlob->getComponent<TransformComponent>().deactivate();
		nBlob->getComponent<SpriteComponent>().deactivate();
		nBlob->getComponent<ColliderComponent>().init();
		nBlob->getComponent<ColorChangeComponent>().updateColor();

	}

};