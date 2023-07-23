#pragma once

#include <vector>
#include "headers/board.hpp"

#define PAWN_VALUE 1
#define KNIGHT_VALUE 3
#define BISHOP_VALUE 3
#define ROOK_VALUE 5
#define QUEEN_VALUE 9

float EvaluatePosition(Board board, int colorToMove);