#pragma once

#include <SDL2/SDL.h>
#include "headers/board.hpp"
#include "headers/eventManager.hpp"
#include "headers/renderer.hpp"
#include "headers/player.hpp"
#include "headers/humanPlayer.hpp"
#include "headers/computerPlayer.hpp"

class Game
{
public:
    void Init();
    void Update();
    void Quit();

private:
    bool running = true;
    Board board;
    EventManager eventManager;
    Renderer renderer;

    HumanPlayer whitePlayer;
    HumanPlayer blackPlayer;
    Player *playerToMove;
    void SwitchTurn(Move move);
};