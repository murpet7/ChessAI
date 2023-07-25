#pragma once

#include <vector>
#include <map>
#include <array>
#include "headers/board.hpp"
#include "headers/gameEnd.hpp"

#define PAWN_VALUE 100
#define KNIGHT_VALUE 320
#define BISHOP_VALUE 330
#define ROOK_VALUE 500
#define QUEEN_VALUE 900

class Evaluator
{
public:
    static float EvaluatePosition(Board &board, int maximizingPlayer);

private:
    static float EvaluateMaterial(Board &board, int maximizingPlayer);
    static float EvaluatePositional(Board &board, int maximizingPlayer);
    static float EvaluatePositionalForPiece(Board &board, int piece, int maximizingPlayer);
    static const std::map<int, std::array<int, 64>> piecePositionTables;
    static const std::array<int, 64> pawnPositionTable;
    static const std::array<int, 64> knightPositionTable;
    static const std::array<int, 64> bishopPositionTable;
    static const std::array<int, 64> rookPositionTable;
    static const std::array<int, 64> queenPositionTable;
    static const std::array<int, 64> kingPositionTable;
};