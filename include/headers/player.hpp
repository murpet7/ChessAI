#pragma once
#include "headers/move.hpp"
#include "headers/board.hpp"

class Player
{
public:
    int colorToMove = WHITE;
    int heldPiece = NONE;
    int heldPieceIndex;
    Board board;
    Player() = default;
    virtual void NotifyTurnToMove(Move move);
    Move GetChosenMove();
    virtual void PickupPiece(int mouseX, int mouseY);
    virtual void DropPiece(int mouseX, int mouseY);

protected:
    bool isMoveChosen = false;
    Move chosenMove;
};