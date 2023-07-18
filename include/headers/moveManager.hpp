#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "headers/board.hpp"
#include "headers/renderer.hpp"
#include "headers/moveGenerator.hpp"

class MoveManager
{
public:
    int GetTileFromMouse(int mouseX, int mouseY);
    void PickupPiece(int x, int y, Board &board);
    void DropPiece(int x, int y, Board &board);
    int GetHeldPiece();
    int GetHeldPieceIndex();
    int GetPlayerToMove();

private:
    int playerToMove = WHITE;
    int heldPiece = NONE;
    int heldPieceIndex;
    bool IsOutOfBounds(int x, int y);
    bool IsOpposingColor(int piece1, int piece2);
    int GetPieceColor(int piece);
    void ReturnHeldPiece(Board &board);
    void MoveHeldPiece(int newSquare, Board &board);
    void FinishTurn();
};