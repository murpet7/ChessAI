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
    static std::vector<Move> GenerateAllLegalMoves(Board board);
    static std::vector<Move> GenerateMovesForPiece(Board board, int square, int heldPiece);
    static Move MovesquaresToMove(Board board, int from, int to, int heldPiece);

private:
    static void GeneratePawnMoves(int pieces[], int square, int colorToMove, int pawnTwoSquareFile, std::vector<Move> &pseudoLegalMoves);
    static void GenerateKnightMoves(int pieces[], int square, int colorToMove, std::vector<Move> &pseudoLegalMoves);
    static void GenerateBishopMoves(int pieces[], int square, int colorToMove, std::vector<Move> &pseudoLegalMoves);
    static void GenerateRookMoves(int pieces[], int square, int colorToMove, std::vector<Move> &pseudoLegalMoves);
    static void GenerateQueenMoves(int pieces[], int square, int colorToMove, std::vector<Move> &pseudoLegalMoves);
    static void GenerateKingMoves(int pieces[], int square, int colorToMove, int castleMask, std::vector<Move> &pseudoLegalMoves);

    static void AddPromotions(int from, int to, std::vector<Move> &pseudoLegalMoves);
    static bool IsCapturableSquare(int pieces[], int square, int colorToMove);
    static bool IsEmptySquare(int pieces[], int square);
    static bool IsEmptySquareOrCapturable(int pieces[], int square, int colorToMove);
    static bool IsKnightOutOfBounds(int oldSquare, int newSquare);
    static bool IsKingOutOfBounds(int oldSquare, int newSquare);
    static int NumSquaresToEdge(int square, int direction);
    static bool IsSquareAttacked(int square, std::vector<Move> moves);

    static void GenerateSlidingMoves(int pieces[], int square, int colorToMove, std::vector<int> directions, std::vector<Move> &pseudoLegalMoves);
    static std::vector<Move> GenerateAllPseudoLegalMoves(std::map<int, std::vector<int>> pieceSquaresOfType, int pieces[], int colorToMove, int pawnTwoSquareFile, int castleMask);
    static std::vector<Move> FilterOnCheck(Board board, std::vector<Move> pseudoLegalMoves);
};