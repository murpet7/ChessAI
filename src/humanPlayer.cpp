#include "headers/humanPlayer.hpp"

int HumanPlayer::GetTileFromMouse(int mouseX, int mouseY)
{
    if (IsOutOfBounds(mouseX, mouseY))
        return -1;
    int tileX = (mouseX - BOARD_X) / TILE_SIZE;
    int tileY = (mouseY - BOARD_Y) / TILE_SIZE;
    return SquareIndex(tileX, tileY);
}

void HumanPlayer::PickupPiece(int mouseX, int mouseY)
{
    heldPieceIndex = GetTileFromMouse(mouseX, mouseY);
    heldPiece = board.pieces[heldPieceIndex];
    std::list<int> &indices = board.pieceSquaresOfType[heldPiece];
    indices.remove(heldPieceIndex);
    if (PieceIsColor(board.colorToMove, heldPiece) || heldPiece == NONE)
        ReturnHeldPiece();
}

void HumanPlayer::DropPiece(int mouseX, int mouseY)
{
    if (heldPiece == NONE)
        return;
    int newSquare = GetTileFromMouse(mouseX, mouseY);
    Move move = ToMove(heldPieceIndex, newSquare, board.colorToMove, board.pieces, heldPiece, board.pawnTwoSquareFile, board);
    if (newSquare != -1 && move.moveValue != 0)
    {
        board.pieces[heldPieceIndex] = heldPiece;
        board.MovePiece(move);
        chosenMove = move;
        isMoveChosen = true;
    }
    else
    {
        ReturnHeldPiece();
    }
}

void HumanPlayer::ReturnHeldPiece()
{
    board.pieces[heldPieceIndex] = heldPiece;
    std::list<int> &indices = board.pieceSquaresOfType[heldPiece];
    indices.push_back(heldPieceIndex);
    heldPiece = NONE;
}

bool HumanPlayer::IsOutOfBounds(int x, int y)
{
    if (x < BOARD_X || x > BOARD_X + TILE_SIZE * ROW_SIZE || y < BOARD_Y || y > BOARD_Y + TILE_SIZE * COLUMN_SIZE)
    {
        return true;
    }
    return false;
}