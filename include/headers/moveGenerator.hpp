#pragma once

#include <list>
#include <map>

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

std::list<Move> GenerateAllPseudoLegalMoves(Board board, int colorToMove, int pawnTwoSquareFile);
std::list<Move> GenerateAllLegalMoves(Board board, int colorToMove, int pawnTwoSquareFile);
std::list<Move> GenerateMovesForPiece(int pieces[], int square, int heldPiece, int colorToMove, int pawnTwoSquareFile, Board board);
std::list<Move> FilterOnCheck(std::list<Move> pseudoLegalMoves, Board board, int colorToMove);
Move ToMove(int from, int to, int colorToMove, int pieces[], int heldPiece, int pawnTwoSquareFile, Board board);

void GeneratePawnMoves(int pieces[], int square, int colorToMove, std::list<Move> &pseudoLegalMoves, int pawnTwoSquareFile);
void GenerateKnightMoves(int pieces[], int square, int colorToMove, std::list<Move> &pseudoLegalMoves);
void GenerateBishopMoves(int pieces[], int square, int colorToMove, std::list<Move> &pseudoLegalMoves);
void GenerateRookMoves(int pieces[], int square, int colorToMove, std::list<Move> &pseudoLegalMoves);
void GenerateQueenMoves(int pieces[], int square, int colorToMove, std::list<Move> &pseudoLegalMoves);
void GenerateKingMoves(int pieces[], int square, int colorToMove, Board board, std::list<Move> &pseudoLegalMoves);
void GenerateSlidingMoves(int pieces[], int square, int colorToMove, std::list<int> directions, std::list<Move> &pseudoLegalMoves);

void AddPromotions(int from, int to, std::list<Move> &pseudoLegalMoves);
bool IsCapturableSquare(int pieces[], int square, int colorToMove);
bool IsEmptySquare(int pieces[], int square);
bool IsEmptySquareOrCapturable(int pieces[], int square, int colorToMove);
bool IsOutOfBounds(int oldSquare, int deltaRank, int deltaFile);
int NumSquaresToEdge(int square, int direction);
bool IsSquareAttacked(int square, std::list<Move> moves);