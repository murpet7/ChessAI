#pragma once

#include <map>
#include <vector>

#include "headers/move.hpp"
#include "headers/boardRepresentation.hpp"
#include "headers/board.hpp"

#define NORTH -8
#define NORTH_EAST -7
#define EAST 1
#define SOUTH_EAST 9
#define SOUTH 8
#define SOUTH_WEST 7
#define WEST -1
#define NORTH_WEST -9

class MoveGenerator
{
public:
    static std::vector<Move> GenerateAllLegalMoves(Board &board);
    static std::vector<Move> GenerateAllPseudoLegalMoves(Board &board);
    static std::vector<Move> GenerateMovesForPiece(Board &board, int square, int heldPiece);
    static Move MovesquaresToMove(Board &board, int from, int to, int heldPiece);

    static bool IsSquareAttacked(int square, std::vector<Move> moves);
    static bool IsEmptySquareOrCapturable(Board &board, int square);

private:
    static void GeneratePawnMoves(Board &board, int square, std::vector<Move> &pseudoLegalMoves);
    static void GenerateKnightMoves(Board &board, int square, std::vector<Move> &pseudoLegalMoves);
    static void GenerateBishopMoves(Board &board, int square, std::vector<Move> &pseudoLegalMoves);
    static void GenerateRookMoves(Board &board, int square, std::vector<Move> &pseudoLegalMoves);
    static void GenerateQueenMoves(Board &board, int square, std::vector<Move> &pseudoLegalMoves);
    static void GenerateKingMoves(Board &board, int square, std::vector<Move> &pseudoLegalMoves);

    static void AddPromotions(int from, int to, std::vector<Move> &pseudoLegalMoves);
    static bool IsCapturableSquare(Board &board, int square);
    static bool IsEmptySquare(Board &board, int square);

    static bool IsKnightOutOfBounds(int oldSquare, int newSquare);
    static bool IsKingOutOfBounds(int oldSquare, int newSquare);
    static int NumSquaresToEdge(int square, int direction);

    static void GenerateSlidingMoves(Board &board, int square, std::vector<int> directions, std::vector<Move> &pseudoLegalMoves);
    static std::vector<Move> FilterOnCheck(Board &board, std::vector<Move> pseudoLegalMoves);
};