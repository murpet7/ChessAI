#pragma once

#include "headers/board.hpp"
#include "headers/moveGenerator.hpp"

#define NOTHING 0
#define CHECKMATE 1
#define STALEMATE 2
#define THREEFOLD_REPETITION 3
#define FIFTY_MOVE_RULE 4
#define INSUFFICIENT_MATERIAL 5

int GetGameEndState(Board board);
int GetCheckmateOrStalemate(Board board);
bool IsThreefoldRepetition(Board board);
bool IsFiftyMoveRule(Board board);
bool IsInsufficientMaterial(Board board);
