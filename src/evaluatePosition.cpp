#include "headers/evaluatePosition.hpp"

float EvaluatePosition(Board board, int colorToMove)
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

    int otherColor = colorToMove == WHITE ? BLACK : WHITE;
    int numGoodPawns = board.pieceSquaresOfType[PAWN | colorToMove].size();
    int numBadPawns = board.pieceSquaresOfType[PAWN | otherColor].size();
    int numGoodKnights = board.pieceSquaresOfType[KNIGHT | colorToMove].size();
    int numBadKnights = board.pieceSquaresOfType[KNIGHT | otherColor].size();
    int numGoodBishops = board.pieceSquaresOfType[BISHOP | colorToMove].size();
    int numBadBishops = board.pieceSquaresOfType[BISHOP | otherColor].size();
    int numGoodRooks = board.pieceSquaresOfType[ROOK | colorToMove].size();
    int numBadRooks = board.pieceSquaresOfType[ROOK | otherColor].size();
    int numGoodQueens = board.pieceSquaresOfType[QUEEN | colorToMove].size();
    int numBadQueens = board.pieceSquaresOfType[QUEEN | otherColor].size();

    return (PAWN_VALUE * (numGoodPawns - numBadPawns)) +
           (KNIGHT_VALUE * (numGoodKnights - numBadKnights)) +
           (BISHOP_VALUE * (numGoodBishops - numBadBishops)) +
           (ROOK_VALUE * (numGoodRooks - numBadRooks)) +
           (QUEEN_VALUE * (numGoodQueens - numBadQueens));
}