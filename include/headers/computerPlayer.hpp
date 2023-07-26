#pragma once
#include <vector>
#include "headers/player.hpp"
#include "headers/moveGenerator.hpp"
#include "headers/searchPositions.hpp"

class ComputerPlayer : public Player
{
    void NotifyTurnToMove(Move move) override;
    void FindBestMove();
};