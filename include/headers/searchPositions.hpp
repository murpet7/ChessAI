#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include "headers/board.hpp"
#include "headers/moveGenerator.hpp"
#include "headers/evaluator.hpp"
float Minimax(Board board, int depth, float alpha, float beta, int maximizingPlayer);
Move GetBestMove(Board board, int depth, int originalColorToMove);
