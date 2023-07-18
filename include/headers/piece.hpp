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

bool IsOpposingColor(int piece1, int piece2);
int GetPieceColor(int piece);
bool PieceIsColor(int piece, int color);
