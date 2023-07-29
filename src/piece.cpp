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

Piece GetPieceType(Piece piece)
{
    return piece & 7;
}

bool PieceIsColor(Piece piece1, Piece piece2)
{
    if (GetPieceColor(piece1) != GetPieceColor(piece2))
        return true;
    return false;
}

bool IsMinorPiece(Piece piece)
{
    if (GetPieceType(piece) == BISHOP || GetPieceType(piece) == KNIGHT)
        return true;
    return false;
}

bool IsMajorPiece(Piece piece)
{
    if (GetPieceType(piece) == ROOK || GetPieceType(piece) == QUEEN)
        return true;
    return false;
}

int OppositeColor(int color)
{
    if (color == WHITE)
        return BLACK;
    return WHITE;
}