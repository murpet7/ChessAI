#pragma once
#include <vector>
#include <thread>
#include "player.hpp"
#include "moveGenerator.hpp"

class ComputerPlayer : public Player
{
    void NotifyTurnToMove(Move move) override;
    void FindBestMove();
};