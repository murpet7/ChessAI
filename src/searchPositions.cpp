#include "headers/searchPositions.hpp"

float Minimax(Board board, int depth, float alpha, float beta, int maximizingPlayer)
{
    if (depth == 0)
        return Evaluator::EvaluatePosition(board, board.colorToMove);

    std::vector<Move> moves = MoveGenerator::GenerateAllLegalMoves(board);
    if (board.colorToMove == maximizingPlayer)
    {
        float maxEval = -INFINITY;
        for (Move move : moves)
        {
            Board newBoard = board;
            newBoard.MakeMove(move);
            float eval = Minimax(newBoard, depth - 1, alpha, beta, maximizingPlayer);
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
        for (Move move : moves)
        {
            Board newBoard = board;
            newBoard.MakeMove(move);
            float eval = Minimax(newBoard, depth - 1, alpha, beta, maximizingPlayer);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}

Move GetBestMove(Board board, int depth, int originalColorToMove)
{
    std::vector<Move> moves = MoveGenerator::GenerateAllLegalMoves(board);
    float maxEval = -INFINITY;
    Move bestMove;
    for (Move move : moves)
    {
        Board newBoard = board;
        newBoard.MakeMove(move);
        float eval = Minimax(newBoard, depth - 1, -INFINITY, INFINITY, originalColorToMove);
        if (eval > maxEval)
        {
            maxEval = eval;
            bestMove = move;
        }
    }
    return bestMove;
}