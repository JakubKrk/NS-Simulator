#pragma once
#include "Game.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <ios>

#include <map>

float getParamValue(float min, float max, std::string message)
{
	float input;

	std::cout << message << std::endl;
	std::cin >> input;
	while (1)
	{
		if (std::cin.fail() || input < min || input > max)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "You have entered wrong input" << std::endl;
			std::cout << message << std::endl;
			std::cin >> input;
		}
		if (input >= min && input <= max) {
			if (!std::cin.fail())
				std::cout << input << std::endl;
				return input;
		}
	}
}

void getInput() {

	std::string A;
	bool defaultv;

	std::cout << "Default values ? <Y/N> : " << std::endl;

	std::cin >> A;

	if (A == "Y") {

		Game::windowH = 800;
		Game::windowW = 800;
		Game::lastGeneration = 50;
		Game::foodForGeneration = 25;
		Game::inhertianceDeviation = 0.05;
		Game::firstGenerationPopulation = 25;
		Game::startingEnergy = 8000;
	}

	if (A == "N") {
		Game::windowH = getParamValue(100, 1200, "Game height : ");
		Game::windowW = getParamValue(100, 2000, "Game width : ");
		Game::foodForGeneration = getParamValue(1, 200, "Food for each generation : ");
		Game::inhertianceDeviation = getParamValue(0, 1, "Deviation of inherited parameters : ");
		Game::firstGenerationPopulation = getParamValue(1, 200, "Blobs in the first generation : ");
		Game::startingEnergy = getParamValue(100, 10000, "Starting energy : ");
		Game::lastGeneration = getParamValue(1, 500, "Generations to simulate : ");
	}

	std::cout << Game::inhertianceDeviation << std::endl;
}