#include "headers/piece.hpp"

bool IsOpposingColor(int piece1, int piece2)
{
    if (GetPieceColor(piece1) != GetPieceColor(piece2))
        return true;
    return false;
}

int GetPieceColor(int piece)
{
    if (piece == NONE)
        return NONE;
    if (piece & WHITE)
        return WHITE;
    return BLACK;
}

bool PieceIsColor(int piece1, int piece2)
{
    if (GetPieceColor(piece1) != GetPieceColor(piece2))
        return true;
    return false;
}