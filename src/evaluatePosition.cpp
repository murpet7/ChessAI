#include "headers/evaluatePosition.hpp"

float EvaluatePosition(Board board, int maximizingPlayer)
{
    int gameEndState = GetGameEndState(board);
    if (gameEndState == CHECKMATE)
    {
        return -1000000;
    }
    if (gameEndState == DRAW)
    {
        return 0;
    }

    int otherColor = maximizingPlayer == WHITE ? BLACK : WHITE;
    int numGoodPawns = board.pieceSquaresOfType[PAWN | maximizingPlayer].size();
    int numBadPawns = board.pieceSquaresOfType[PAWN | otherColor].size();
    int numGoodKnights = board.pieceSquaresOfType[KNIGHT | maximizingPlayer].size();
    int numBadKnights = board.pieceSquaresOfType[KNIGHT | otherColor].size();
    int numGoodBishops = board.pieceSquaresOfType[BISHOP | maximizingPlayer].size();
    int numBadBishops = board.pieceSquaresOfType[BISHOP | otherColor].size();
    int numGoodRooks = board.pieceSquaresOfType[ROOK | maximizingPlayer].size();
    int numBadRooks = board.pieceSquaresOfType[ROOK | otherColor].size();
    int numGoodQueens = board.pieceSquaresOfType[QUEEN | maximizingPlayer].size();
    int numBadQueens = board.pieceSquaresOfType[QUEEN | otherColor].size();

    return -((PAWN_VALUE * (numGoodPawns - numBadPawns)) +
             (KNIGHT_VALUE * (numGoodKnights - numBadKnights)) +
             (BISHOP_VALUE * (numGoodBishops - numBadBishops)) +
             (ROOK_VALUE * (numGoodRooks - numBadRooks)) +
             (QUEEN_VALUE * (numGoodQueens - numBadQueens)));
}