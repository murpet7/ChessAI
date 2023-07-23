#include "headers/searchPositions.hpp"

std::tuple<int, Move> Minimax(Board board, int depth, int maximizingPlayer)
{
    // MAAK HIER MINMAX VAN JIJ IDIOOT
    // printf("Minimax called %p\n", depth);
    std::vector<std::tuple<int, Move>> gameStates;
    if (depth == 0)
    {
        return std::make_tuple(EvaluatePosition(board, board.colorToMove), Move());
    }

    std::vector<Move> moves = GenerateAllLegalMoves(board, board.colorToMove, board.pawnTwoSquareFile);
    std::vector<std::tuple<int, Move>> newGameStates;
    for (Move move : moves)
    {
        Board newBoard = board;
        newBoard.MovePiece(move);
        std::tuple<int, Move> newGameState = std::make_tuple(std::get<0>(Minimax(newBoard, depth - 1, maximizingPlayer)), move);
        gameStates.push_back(newGameState);
    }
    if (gameStates.size() == 0)
    {
        return std::make_tuple(EvaluatePosition(board, board.colorToMove), Move());
    }
    if (board.colorToMove == maximizingPlayer)
    {
        std::sort(gameStates.begin(), gameStates.end(), [](const std::tuple<int, Move> &a, const std::tuple<int, Move> &b)
                  { return std::get<0>(a) < std::get<0>(b); });
        return gameStates[0];
    }
    else
    {
        std::sort(gameStates.begin(), gameStates.end(), [](const std::tuple<int, Move> &a, const std::tuple<int, Move> &b)
                  { return std::get<0>(a) > std::get<0>(b); });
        return gameStates[0];
    }
}

Move GetBestMove(Board board, int depth, int originalColorToMove)
{
    std::tuple<int, Move> gameStates = Minimax(board, depth, originalColorToMove);
    return std::get<1>(gameStates);
}