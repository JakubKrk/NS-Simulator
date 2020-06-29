#pragma once
#include "LCS.h"
#include "Formulas.h"
#include <algorithm>
#include <fstream>
//#include <Python.h>

//void runPython()
//{
//	char filename[] = "Grapher.py";
//	FILE* fp;
//
//
//	fp = _Py_fopen(filename, "r");
//	PyRun_SimpleFile(fp, filename);
//
//	std::cout << "Python run" << std::endl;
//
//}

struct LoggingFormula : public Formula
{
	 
	LogicController* lController;	int previousGeneration = -1;

	void init() override
	{

		std::ofstream myfile("blobs.csv", std::ios::app);
		myfile << Game::lastGeneration << ";";
		myfile << "\n";
		myfile.close();
		/*auto& graphs(lController->manager->getGroup(groupPlots));
		for (auto& g : graphs) {
			g->getComponent<SpriteComponent>().updateTexture();
		}*/
	}

	void update() override
	{
		if (Game::generation != previousGeneration)
		{
			auto& blobs(lController->manager->getGroup(groupBlobsActive));

			std::ofstream myfile("blobs.csv", std::ios::app);
			myfile << Game::generation << ";";
			myfile << blobs.size() << ";";
			for (auto& b : blobs) {
				myfile << b->speed <<  ";" << b->size << ";" << b->sight << ";";
			}
			myfile << "\n";
			myfile.close();



			//runPython();


			//auto& graphs(lController->manager->getGroup(groupPlots));
			//for (auto& g : graphs) {
			//	g->getComponent<SpriteComponent>().updateTexture();
			//}

			previousGeneration = Game::generation;


		}

	}


};
