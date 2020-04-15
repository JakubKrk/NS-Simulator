#include "Game.h"

Game* game = nullptr;

static int WindowW = 1200;
static int WindowH = 800;


int main(int argc, char* argv[])
{   
    const int FPS = 2000;
    static const int* pFPS = &FPS;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();

    game->init("Test 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowW, WindowH, false);

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

    return 0;
}