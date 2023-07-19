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
    std::list<int> &indices = board.pieceSquaresOfType[heldPiece];
    indices.remove(heldPieceIndex);
    if (PieceIsColor(heldPiece, playerToMove) || heldPiece == NONE)
        ReturnHeldPiece(board);
}

void MoveManager::DropPiece(int x, int y, Board &board)
{
    if (heldPiece == NONE)
        return;
    int newSquare = GetTileFromMouse(x, y);
    Move move = MoveFromStartAndEnd(heldPieceIndex, newSquare, playerToMove, board.pieces, heldPiece, pawnTwoSquareFile);
    if (newSquare != -1 && move.moveValue != 0)
    {
        MoveHeldPiece(move, board);
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
    std::list<int> &indices = board.pieceSquaresOfType[heldPiece];
    indices.push_back(heldPieceIndex);
    heldPiece = NONE;
}

void MoveManager::MoveHeldPiece(Move move, Board &board)
{
    board.pieces[move.GetTo()] = heldPiece;
    std::list<int> &indices = board.pieceSquaresOfType[heldPiece];
    indices.push_back(move.GetTo());
    heldPiece = NONE;

    if (move.GetFlag() == PAWN_TWO_SQUARES)
        pawnTwoSquareFile = FileIndex(move.GetTo());
    else
        pawnTwoSquareFile = -2;

    if (move.GetFlag() == EN_PASSANT)
    {
        int captureSquare = SquareIndex(FileIndex(move.GetTo()), RankIndex(move.GetFrom()));
        board.pieces[captureSquare] = NONE;
    }
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

int MoveManager::GetHeldPiece()
{
    return heldPiece;
}

int MoveManager::GetPlayerToMove()
{
    return playerToMove;
}

int MoveManager::GetHeldPieceIndex()
{
    return heldPieceIndex;
}

int MoveManager::GetPawnTwoSquareFile()
{
    return pawnTwoSquareFile;
}