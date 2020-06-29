#include "Game.h"
#include "Formulas.h"
#include "LCS.h"
#include "Input.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <ios>

SDL_Renderer* Game::renderer;
SDL_Event Game::event;
Manager* Game::manager = new Manager();
LogicController* Game::logic = new LogicController(Game::manager);
Board* Game::board;
GameState Game::state;
int Game::generation;
int Game::lastGeneration;
int Game::windowH;
int Game::windowW;
int Game::blobsAressionDelay;
int Game::foodForGeneration;
float Game::inhertianceDeviation;
int Game::firstGenerationPopulation;
float Game::startingEnergy;
bool Game::aggresion;
bool start = true;


Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, bool fullscreen)
{

	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}

	getInput();

	Game::generation = 0;
	Game::blobsAressionDelay = 100;
	Game::aggresion = false;
	Game::state = ghunting;

	board = new Board(static_cast<int>(Game::windowW / 2), static_cast<int>(Game::windowH / 2), (Game::windowW -50), (Game::windowH - 50));

	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems inited!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, Game::windowW, Game::windowH, flags);
		if (window) {
			std::cout << "Window created!..." << std::endl;
		}

		SDL_Surface* icon = IMG_Load("assets/icon.png");
		SDL_SetWindowIcon(window, icon);
		SDL_FreeSurface(icon);
	
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 53, 92, 48, 100);
			std::cout << "Renderer created!..." << std::endl;
		}

		isRunning = true;
	}
	else{
		isRunning = false;
	}

	logic->SpawnEnviroment();
	logic->SpawnFood(Game::foodForGeneration);
	logic->SpawnBlobs(Game::firstGenerationPopulation);
	
	logic->addComponent<GameStatesFormula>();
	logic->addComponent<FoodEatingFormula>();
	logic->addComponent<BlobsEatingFormula>();
	logic->addComponent<WallCollisionFormula>();
	logic->addComponent<SightFormula>();
	logic->addComponent<ReturningBlobsFormula>();
	logic->addComponent<ReproducingFormula>();
	logic->addComponent<EnergyFormula>();
	logic->addComponent<OutOfBoardFormula>();
	logic->addComponent<LoggingFormula>();

}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		remove("blobs.csv");
		break;

	default:
		break;
	}
}

void Game::update()
{
	if (Game::state != generationspassed){
		manager->update();
		logic->update();
	}
}

void Game::render()
{

	SDL_RenderClear(renderer);

	manager->draw();

	SDL_RenderPresent(renderer);

	if (start)
	{
		SDL_Delay(2000);
		start = false;
	}

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned!" << std::endl;
}




