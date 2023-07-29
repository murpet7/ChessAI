#include "headers/gameEnd.hpp"

int GetGameEndState(Board &board)
{
    int checkOrStaleMate = GetCheckmateOrStalemate(board);
    if (checkOrStaleMate != NOTHING)
    {
        return checkOrStaleMate;
    }
    if (IsThreefoldRepetition(board))
    {
        return DRAW;
    }
    if (IsFiftyMoveRule(board))
    {
        return DRAW;
    }
    if (IsInsufficientMaterial(board))
    {
        return DRAW;
    }
    return NOTHING;
}

int GetCheckmateOrStalemate(Board &board)
{
    std::vector<Move> opponentMoves;
    MoveGenerator::GenerateAllPseudoLegalMoves(board, opponentMoves);
    int kingSquare = board.GetKingSquare(board.GetColorToMove());
    if (kingSquare == -1)
    {
        printf("Error: No king found\n");
        return DRAW; // TODO: Check if this is correct
    }

    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            int square = kingSquare + x + y * 8;
            if (x == 0 && y == 0)
                continue; // Skip the king's position
            if (!MoveGenerator::IsEmptySquareOrCapturable(board, square) && !MoveGenerator::IsSquareAttacked(square, opponentMoves))
            {
                return NOTHING;
            }
        }
    }

    if (MoveGenerator::IsSquareAttacked(kingSquare, opponentMoves))
    {
        return CHECKMATE;
    }

    return DRAW;
}

bool IsThreefoldRepetition(Board &board)
{
    return false;
}

bool IsFiftyMoveRule(Board &board)
{
    return false;
}

bool IsInsufficientMaterial(Board &board)
{
    if (board.GetPieceSquares(PAWN | WHITE).size() > 0 || board.GetPieceSquares(PAWN | BLACK).size() > 0)
    {
        return false;
    }
    if (board.GetPieceSquares(ROOK | WHITE).size() > 0 || board.GetPieceSquares(ROOK | BLACK).size() > 0)
    {
        return false;
    }
    if (board.GetPieceSquares(QUEEN | WHITE).size() > 0 || board.GetPieceSquares(QUEEN | BLACK).size() > 0)
    {
        return false;
    }
    if (board.GetPieceSquares(BISHOP | WHITE).size() > 1 || board.GetPieceSquares(BISHOP | BLACK).size() > 1)
    {
        return false;
    }
    if (board.GetPieceSquares(BISHOP | WHITE).size() > 0 && board.GetPieceSquares(KNIGHT | WHITE).size() > 0)
    {
        return false;
    }
    if (board.GetPieceSquares(BISHOP | BLACK).size() > 0 && board.GetPieceSquares(KNIGHT | BLACK).size() > 0)
    {
        return false;
    }
    if (board.GetPieceSquares(KNIGHT | WHITE).size() > 2 || board.GetPieceSquares(KNIGHT | BLACK).size() > 2)
    {
        return false;
    }
    return true;
}