#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include "headers/board.hpp"
#include "headers/moveGenerator.hpp"
#include "headers/evaluatePosition.hpp"

std::tuple<int, Move> Minimax(Board board, int depth, int maximizingPlayer);
Move GetBestMove(Board board, int depth, int originalColorToMove);
