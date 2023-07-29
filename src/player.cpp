#include "headers/player.hpp"

void Player::NotifyTurnToMove(Move move)
{
    if (move.moveValue != 0)
        board.MakeMove(move);
}

Move Player::GetChosenMove()
{
    if (isMoveChosen)
    {
        board.MakeMove(chosenMove);
        isMoveChosen = false;
        heldPiece = NONE;
        return chosenMove;
    }
    return Move();
}

void Player::PickupPiece(int mouseX, int mouseY) {}

void Player::DropPiece(int mouseX, int mouseY) {}