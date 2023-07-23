#include "headers/piece.hpp"

bool IsOpposingColor(Piece piece1, Piece piece2)
{
    if (GetPieceColor(piece1) != GetPieceColor(piece2))
        return true;
    return false;
}

Color GetPieceColor(Piece piece)
{
    return piece & 24;
}

bool PieceIsColor(Piece piece1, Piece piece2)
{
    if (GetPieceColor(piece1) != GetPieceColor(piece2))
        return true;
    return false;
}