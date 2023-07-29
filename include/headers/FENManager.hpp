#pragma once
#include <string>
#include <vector>
#include "headers/board.hpp"
#include "headers/boardRepresentation.hpp"
class FENManager
{
public:
    static int *PiecesFromFEN(Board &board, std::string FEN);

private:
    static int PieceTypeFromChar(char c);
};