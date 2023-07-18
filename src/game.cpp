#include "headers/game.hpp"

void Game::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    running = true;
    while (running)
    {
        Update();
    }
}

void Game::Update()
{
    eventManager.Update(running, moveManager, board);
    renderer.Update(board, moveManager.GetHeldPiece(), moveManager.GetHeldPieceIndex(), moveManager.GetPlayerToMove());
}

void Game::Quit()
{
    renderer.Destroy();
    running = false;
}