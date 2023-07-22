#pragma once
#include <vector>
#include "player.hpp"
#include "moveGenerator.hpp"

class ComputerPlayer : public Player
{
    void NotifyTurnToMove(Move move) override;
};