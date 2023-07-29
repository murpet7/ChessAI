#include "headers/computerPlayer.hpp"
#include <ctime>
#include <chrono>
#include <iomanip>
#include <iostream>
#include "threads/mingw.thread.h"

void ComputerPlayer::NotifyTurnToMove(Move move)
{
    if (move.moveValue != 0)
        board.MakeMove(move);

    // std::thread t(&ComputerPlayer::FindBestMove, this);
    // t.detach();
    FindBestMove();
}

void ComputerPlayer::FindBestMove()
{
    std::clock_t c_start = std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();
    chosenMove = PositionSearcher::GetBestMove(board, 3);
    std::clock_t c_end = std::clock();
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
              << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
              << "Wall clock time passed: "
              << std::chrono::duration<double, std::milli>(t_end - t_start).count()
              << " ms\n"
              << Evaluator::EvaluatePosition(board, board.GetColorToMove()) << "\n";
    isMoveChosen = true;
}