#pragma once

#include "headers/board.hpp"
#include "headers/moveGenerator.hpp"

#define NOTHING 0
#define DRAW 1
#define CHECKMATE 2

int GetGameEndState(Board &board);
int GetCheckmateOrStalemate(Board &board);
bool IsThreefoldRepetition(Board &board);
bool IsFiftyMoveRule(Board &board);
bool IsInsufficientMaterial(Board &board);
