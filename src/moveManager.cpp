#include "headers/moveManager.hpp"

int MoveManager::GetTileFromMouse(int mouseX, int mouseY)
{
    if (IsOutOfBounds(mouseX, mouseY))
        return -1;
    int tileX = (mouseX - BOARD_X) / TILE_SIZE;
    int tileY = (mouseY - BOARD_Y) / TILE_SIZE;
    return SquareIndex(tileX, tileY);
}

void MoveManager::PickupPiece(int x, int y, Board &board)
{
    heldPieceIndex = GetTileFromMouse(x, y);
    heldPiece = board.pieces[heldPieceIndex];
    board.pieces[heldPieceIndex] = NONE;
    if (GetPieceColor(heldPiece) != playerToMove || heldPiece == NONE)
        ReturnHeldPiece(board);
}

void MoveManager::DropPiece(int x, int y, Board &board)
{
    if (heldPiece == NONE)
        return;
    int newSquare = GetTileFromMouse(x, y);
    if (newSquare != -1 && newSquare != heldPieceIndex && (board.pieces[newSquare] == NONE || IsOpposingColor(heldPiece, board.pieces[newSquare])))
    {
        MoveHeldPiece(newSquare, board);
        FinishTurn();
    }
    else
    {
        ReturnHeldPiece(board);
    }
}

void MoveManager::ReturnHeldPiece(Board &board)
{
    board.pieces[heldPieceIndex] = heldPiece;
    heldPiece = NONE;
}

void MoveManager::MoveHeldPiece(int newSquare, Board &board)
{
    board.pieces[newSquare] = heldPiece;
    heldPiece = NONE;
}

void MoveManager::FinishTurn()
{
    if (playerToMove == WHITE)
        playerToMove = BLACK;
    else
        playerToMove = WHITE;
}

bool MoveManager::IsOutOfBounds(int x, int y)
{
    if (x < BOARD_X || x > BOARD_X + TILE_SIZE * ROW_SIZE || y < BOARD_Y || y > BOARD_Y + TILE_SIZE * COLUMN_SIZE)
    {
        return true;
    }
    return false;
}

bool MoveManager::IsOpposingColor(int piece1, int piece2)
{
    if (GetPieceColor(piece1) != GetPieceColor(piece2))
        return true;
    return false;
}

int MoveManager::GetPieceColor(int piece)
{
    if (piece == NONE)
        return NONE;
    if (piece & WHITE)
        return WHITE;
    return BLACK;
}

int MoveManager::GetHeldPiece()
{
    return heldPiece;
}