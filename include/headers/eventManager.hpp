#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "board.hpp"
#include "headers/player.hpp"

class EventManager
{
public:
    void Update(bool &running, Player &playerToMove);

private:
    void OnMouseDown(Player &playerToMove);
    void OnMouseUp(Player &playerToMove);
};