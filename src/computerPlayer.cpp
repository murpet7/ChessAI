#include "headers/computerPlayer.hpp"

void ComputerPlayer::NotifyTurnToMove(Move move)
{
    if (move.moveValue != 0)
        board.MovePiece(move);

    // std::thread t(&ComputerPlayer::FindBestMove, this);
    // t.detach();
    FindBestMove();
}

void ComputerPlayer::FindBestMove()
{
    chosenMove = GetBestMove(board, 3, board.colorToMove);
    board.MovePiece(chosenMove);
    isMoveChosen = true;
}