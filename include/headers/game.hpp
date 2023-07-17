#pragma once

#include <SDL2/SDL.h>
#include "headers/board.hpp"
#include "headers/eventManager.hpp"
#include "headers/renderer.hpp"
#include "headers/moveManager.hpp"

class Game
{
public:
    void Init();
    void Update();
    void Quit();

private:
    Board board;
    EventManager eventManager;
    MoveManager moveManager;
    Renderer renderer;
    bool running = true;
};