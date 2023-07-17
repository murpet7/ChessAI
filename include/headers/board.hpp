#pragma once

#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "headers/piece.hpp"
#include "headers/boardRepresentation.hpp"

#define BOARD_X 0
#define BOARD_Y 0
#define TILE_SIZE 80
#define ROW_SIZE 8
#define COLUMN_SIZE 8

class Board
{
public:
    Board();
    int pieces[64] = {NONE};
    void PiecesFromFEN(std::string FEN);
};