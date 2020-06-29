#include "Game.h"
#include "Python.h"

Game* game = nullptr;


int main(int argc, char* argv[])
{   
    const int FPS = 200;
    static const int* pFPS = &FPS;
    const int frameDelay = 1000 / FPS;
    Py_Initialize();

    Uint32 frameStart;
    int frameTime;

    game = new Game();

    game->init("Natural selection simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);

    while (game->running()) {

        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }

    }

    game->clean();
    Py_Finalize();
    return 0;
}