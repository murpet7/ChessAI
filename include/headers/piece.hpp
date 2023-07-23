#pragma once

#define NONE 0
#define PAWN 1
#define KNIGHT 2
#define BISHOP 3
#define ROOK 4
#define QUEEN 5
#define KING 6

#define WHITE 8
#define BLACK 16

#define Piece int
#define Color int

bool IsOpposingColor(Piece piece1, Piece piece2);
Color GetPieceColor(Piece piece);
Piece GetPieceType(Piece piece);
bool PieceIsColor(Piece piece, Color color);
