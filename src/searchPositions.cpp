#include "headers/searchPositions.hpp"
#include <stdlib.h>

float PositionSearcher::Minimax(Board &board, int depth, float alpha, float beta, int maximizingPlayer)
{
    if (depth == 0)
        return Evaluator::EvaluatePosition(board, maximizingPlayer);

    std::vector<Move> legalMoves;
    MoveGenerator::GenerateAllLegalMoves(board, legalMoves);
    if ((legalMoves).size() == 0)
    {
        if (GetGameEndState(board) == CHECKMATE)
            return -INFINITY;
        else
            return 0;
    }
    if (board.GetColorToMove() == maximizingPlayer)
    {
        float maxEval = -INFINITY;
        for (Move move : legalMoves)
        {
            board.MakeMove(move);
            float eval = Minimax(board, depth - 1, alpha, beta, maximizingPlayer);
            board.UndoMove(move);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha)
                break;
        }
        return maxEval;
    }
    else
    {
        float minEval = INFINITY;
        for (Move move : legalMoves)
        {
            board.MakeMove(move);
            float eval = Minimax(board, depth - 1, alpha, beta, maximizingPlayer);
            board.UndoMove(move);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}

Move PositionSearcher::GetBestMove(Board &board, int depth)
{
    std::vector<Move> legalMoves;
    MoveGenerator::GenerateAllLegalMoves(board, legalMoves);
    float maxEval = -INFINITY;
    Move bestMove;
    int color = board.GetColorToMove();
    for (Move move : legalMoves)
    {
        board.MakeMove(move);
        float eval = Minimax(board, depth - 1, -INFINITY, INFINITY, color);
        board.UndoMove(move);
        if (eval > maxEval)
        {
            maxEval = eval;
            bestMove = move;
        }
    }
    return bestMove;
}