#include "headers/player.hpp"

void Player::NotifyTurnToMove(Move move)
{
    board.MovePiece(move);
}

Move Player::GetChosenMove()
{
    if (isMoveChosen)
        return chosenMove;
    return Move();
}

void Player::PickupPiece(int mouseX, int mouseY) {}

void Player::DropPiece(int mouseX, int mouseY) {}