#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <iomanip>
#include <vector>

class ColliderComponent;
class LogicController;
class Manager;
class Board;

using GameState = std::size_t;

static enum gamestates : std::size_t {

	ghunting,
	greturning,
	gwaiting,
	greproducing,
	generationspassed,

};

class Game
{
public:


	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }

	static Board* board;
	static LogicController* logic;
	static Manager* manager;
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static GameState state;
	static bool aggresion;
	static int blobsAressionDelay;
	static int generation;
	static int lastGeneration;
	static int foodForGeneration;
	static float inhertianceDeviation;
	static float startingEnergy;
	static int firstGenerationPopulation;
	static int windowH;
	static int windowW;

private:

	int cnt;
	bool isRunning;
	SDL_Window* window;

};

