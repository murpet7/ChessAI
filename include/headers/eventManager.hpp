#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "board.hpp"

class EventManager
{
public:
    void Update(bool &running, Board &board);

private:
    void OnMouseDown(Board &board);
    void OnMouseUp(Board &board);
};