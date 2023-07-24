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

int GetCheckmateOrStalemate(Board board)
{
    std::vector<Move> opponentMoves = MoveGenerator::GenerateAllPseudoLegalMoves(board.pieceSquaresOfType, board.pieces, board.colorToMove, board.pawnTwoSquareFile, board.castleMask);
    // int kingSquare = board.GetKingSquare(board.colorToMove);
    //
    // for (int y = -1; y <= 1; y++)
    //{
    //    for (int x = -1; x <= 1; x++)
    //    {
    //        int square = kingSquare + x + y * 8;
    //        if (x == 0 && y == 0)
    //            continue; // Skip the king's position
    //        if (!MoveGenerator::IsEmptySquareOrCapturable(board.pieces, square, board.colorToMove) && !MoveGenerator::IsSquareAttacked(square, opponentMoves))
    //        {
    //            return NOTHING;
    //        }
    //    }
    //}
    //
    // if (MoveGenerator::IsSquareAttacked(kingSquare, opponentMoves))
    //{
    //    return CHECKMATE;
    //}
    //
    // return DRAW;
    return false;
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
    // if (board.pieceSquaresOfType[PAWN | WHITE].size() > 0 || board.pieceSquaresOfType[PAWN | BLACK].size() > 0)
    // {
    //     return false;
    // }
    // if (board.pieceSquaresOfType[ROOK | WHITE].size() > 0 || board.pieceSquaresOfType[ROOK | BLACK].size() > 0)
    // {
    //     return false;
    // }
    // if (board.pieceSquaresOfType[QUEEN | WHITE].size() > 0 || board.pieceSquaresOfType[QUEEN | BLACK].size() > 0)
    // {
    //     return false;
    // }
    // if (board.pieceSquaresOfType[BISHOP | WHITE].size() > 1 || board.pieceSquaresOfType[BISHOP | BLACK].size() > 1)
    // {
    //     return false;
    // }
    // if (board.pieceSquaresOfType[BISHOP | WHITE].size() > 0 && board.pieceSquaresOfType[KNIGHT | WHITE].size() > 0)
    // {
    //     return false;
    // }
    // if (board.pieceSquaresOfType[BISHOP | BLACK].size() > 0 && board.pieceSquaresOfType[KNIGHT | BLACK].size() > 0)
    // {
    //     return false;
    // }
    // if (board.pieceSquaresOfType[KNIGHT | WHITE].size() > 2 || board.pieceSquaresOfType[KNIGHT | BLACK].size() > 2)
    // {
    //     return false;
    // }
    // return true;
    return false;
}