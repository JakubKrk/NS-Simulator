#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <iomanip>
// "ECS.h"
//#include "LCS.h"
//#include "Board.h"
#include <vector>

class ColliderComponent;
class LogicController;
class Manager;
class Board;

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

private:

	int cnt;
	bool isRunning;
	SDL_Window* window;

};

