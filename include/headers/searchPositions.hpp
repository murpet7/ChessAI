#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include "headers/board.hpp"
#include "headers/moveGenerator.hpp"
#include "headers/evaluator.hpp"

#define INFINITY 1000000

class PositionSearcher
{
public:
    static Move GetBestMove(Board &board, int depth, int originalColorToMove);

private:
    static float Minimax(Board &board, int depth, float alpha, float beta, int maximizingPlayer);
};