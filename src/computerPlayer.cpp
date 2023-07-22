#include "headers/computerPlayer.hpp"

void ComputerPlayer::NotifyTurnToMove(Move move)
{
    board.MovePiece(move);

    std::vector<Move> legalMoves = GenerateAllLegalMoves(board, board.colorToMove, board.pawnTwoSquareFile);
    chosenMove = legalMoves[rand() % legalMoves.size()];
    board.MovePiece(chosenMove);
    isMoveChosen = true;
}