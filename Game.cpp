#include "Game.h"
#include "Formulas.h"
#include "LCS.h"

SDL_Renderer* Game::renderer;
SDL_Event Game::event;
Manager* Game::manager = new Manager();
LogicController* Game::logic = new LogicController(Game::manager);
Board* Game::board;

bool start = true;


Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

	board = new Board(static_cast<int>(width/3), static_cast<int>(height/2), (3*(width/5)), (height - 100));
	//static BlobManager blobManager(manager, board);

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems inited!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created!..." << std::endl;
		}


	
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!..." << std::endl;
		}

		isRunning = true;
	}
	else{
		isRunning = false;
	}


	//blobManager.createBlobs(10);

	logic->CreateEnviroment();
	//Blob* blobek = manager->addEntity<Blob>();
	//blobek->speak();
	//logic->CreateBlob();
	logic->SpawnFood(50);
	logic->SpawnBlobs(50);
	logic->addComponent<FoodEatingFormula>();
	logic->addComponent<WallCollisionFormula>();
	logic->addComponent<ReturningBlobsFormula>();
	logic->addComponent<EnergyFormula>();
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update()
{
	/*auto& blob(manager->getGroup(groupBlobsActive));

	for (auto* b : blob)
	{
		b->speak();
	}*/

	manager->refresh();
	manager->update();
	logic->update();
}

void Game::render()
{

	SDL_RenderClear(renderer);

	//auto& blobs(manager->getGroup(groupBlobsActive));
	//auto& background(manager->getGroup(groupBackground));


	//for (auto& b : background)
	//{
	//	b->draw();
	//}

	//for (auto& bl : blobs)
	//{
	//	bl->draw();
	//}

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




