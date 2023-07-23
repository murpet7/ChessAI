#include "headers/humanPlayer.hpp"

int HumanPlayer::GetTileFromMouse(int mouseX, int mouseY)
{
    if (IsOutOfBounds(mouseX, mouseY))
        return -1;
    int tileX = (mouseX - BOARD_X) / TILE_SIZE;
    int tileY = (mouseY - BOARD_Y) / TILE_SIZE;
    return Square(tileX, tileY);
}

void HumanPlayer::PickupPiece(int mouseX, int mouseY)
{
    heldPieceIndex = GetTileFromMouse(mouseX, mouseY);
    heldPiece = board.pieces[heldPieceIndex];
    if (PieceIsColor(board.colorToMove, heldPiece))
        heldPiece = NONE;
}

void HumanPlayer::DropPiece(int mouseX, int mouseY)
{
    if (heldPiece == NONE)
        return;
    int newSquare = GetTileFromMouse(mouseX, mouseY);
    Move move = MoveGenerator::MovesquaresToMove(board, heldPieceIndex, newSquare, heldPiece);
    if (newSquare != -1 && move.moveValue != 0)
    {
        board.MovePiece(move);
        chosenMove = move;
        isMoveChosen = true;
    }
    else
    {
        heldPiece = NONE;
    }
}

bool HumanPlayer::IsOutOfBounds(int x, int y)
{
    if (x < BOARD_X || x > BOARD_X + TILE_SIZE * ROW_SIZE || y < BOARD_Y || y > BOARD_Y + TILE_SIZE * COLUMN_SIZE)
    {
        return true;
    }
    return false;
}