#include "headers/chess.hpp"

void Chess::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Window *window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    EventManager eventManager = EventManager();
    board = Board(renderer);
    board.DrawBoard(renderer);
    running = true;
    while (running)
    {
        eventManager.Update(running, board);
        SDL_SetRenderDrawColor(renderer, 170, 170, 170, 255);
        SDL_RenderClear(renderer);
        board.Draw(renderer);
        SDL_RenderPresent(renderer);
    }
}

void Chess::Quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    running = false;
}