#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "board.hpp"
#include "moveManager.hpp"

class EventManager
{
public:
    void Update(bool &running, MoveManager &moveManager, Board &board);

private:
    void OnMouseDown(MoveManager &moveManager, Board &board);
    void OnMouseUp(MoveManager &moveManager, Board &board);
};