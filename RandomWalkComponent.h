#pragma once

#include "ECS.h"
#include "Components.h"
#include <random>
#include <iostream>
#include <chrono>

class RandomWalkComponent : public Component
{
public:

	TransformComponent* transfrom;

	float deviation;
	float mean;
	int counter, countermax;

	RandomWalkComponent(float dev)
	{
		this->deviation = dev;
		this->mean = 0.00f;
		this->counter = rand() % 15;
		this->countermax = 10 + rand() % 40;
	}

	void init() override
	{
		transfrom = &entity->getComponent<TransformComponent>();
		activate();
	}


	void update() override
	{
		if (isActive()) {
				if (counter > countermax) {
					transfrom->velocity.setAngle(transfrom->velocity.A() + calcRandom());
					counter = 0;
				}
				counter++;
		}
	}

	
	float calcRandom() {
		unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
		std::default_random_engine e(seed);
		mean = transfrom->velocity.A();
		std::normal_distribution<double> distribution(90, deviation);
		return 90 - distribution(e);
	}
};