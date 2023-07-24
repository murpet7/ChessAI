#include "headers/gameEnd.hpp"

int GetGameEndState(Board board)
{
    int checkOrStaleMate = GetCheckmateOrStalemate(board);
    if (checkOrStaleMate != NOTHING)
    {
        return checkOrStaleMate;
    }
    if (IsThreefoldRepetition(board))
    {
        return THREEFOLD_REPETITION;
    }
    if (IsFiftyMoveRule(board))
    {
        return FIFTY_MOVE_RULE;
    }
    if (IsInsufficientMaterial(board))
    {
        return INSUFFICIENT_MATERIAL;
    }
    return NOTHING;
}

int GetCheckmateOrStalemate(Board board)
{
    std::vector<Move> opponentMoves = MoveGenerator::GenerateAllPseudoLegalMoves(board.pieceSquaresOfType, board.pieces, board.colorToMove, board.pawnTwoSquareFile, board.castleMask);
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            int square = board.GetKingSquare(board.colorToMove) + x + y * 8;
            if (!MoveGenerator::IsSquareAttacked(square, opponentMoves) && !MoveGenerator::IsEmptySquareOrCapturable(board.pieces, square, board.colorToMove))
            {
                return NOTHING;
            }
        }
    }
    if (MoveGenerator::IsSquareAttacked(board.GetKingSquare(board.colorToMove), opponentMoves))
    {
        return CHECKMATE;
    }
    return STALEMATE;
}

bool IsThreefoldRepetition(Board board)
{
    return false;
}

bool IsFiftyMoveRule(Board board)
{
    return false;
}

bool IsInsufficientMaterial(Board board)
{
    if (board.pieceSquaresOfType[PAWN | WHITE].size() > 0 || board.pieceSquaresOfType[PAWN | BLACK].size() > 0)
    {
        return false;
    }
    if (board.pieceSquaresOfType[ROOK | WHITE].size() > 0 || board.pieceSquaresOfType[ROOK | BLACK].size() > 0)
    {
        return false;
    }
    if (board.pieceSquaresOfType[QUEEN | WHITE].size() > 0 || board.pieceSquaresOfType[QUEEN | BLACK].size() > 0)
    {
        return false;
    }
    if (board.pieceSquaresOfType[BISHOP | WHITE].size() > 1 || board.pieceSquaresOfType[BISHOP | BLACK].size() > 1)
    {
        return false;
    }
    if (board.pieceSquaresOfType[BISHOP | WHITE].size() > 0 && board.pieceSquaresOfType[KNIGHT | WHITE].size() > 0)
    {
        return false;
    }
    if (board.pieceSquaresOfType[BISHOP | BLACK].size() > 0 && board.pieceSquaresOfType[KNIGHT | BLACK].size() > 0)
    {
        return false;
    }
    if (board.pieceSquaresOfType[KNIGHT | WHITE].size() > 2 || board.pieceSquaresOfType[KNIGHT | BLACK].size() > 2)
    {
        return false;
    }
    return true;
}