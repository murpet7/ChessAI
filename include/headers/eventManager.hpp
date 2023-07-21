#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "board.hpp"
#include "headers/player.hpp"

class EventManager
{
public:
    void Update(bool &running, Board &board, Player &playerToMove);

private:
    void OnMouseDown(Board &board, Player &playerToMove);
    void OnMouseUp(Board &board, Player &playerToMove);
};