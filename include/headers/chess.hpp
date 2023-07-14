#pragma once

#include <SDL2/SDL.h>
#include "board.hpp"
#include "eventManager.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Chess
{
public:
    void Init();
    void Quit();
    int curPlayerColor = White;

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    Board board;
    bool running = true;
};