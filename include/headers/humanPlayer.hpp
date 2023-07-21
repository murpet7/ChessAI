#pragma once
#include "headers/player.hpp"
#include "headers/board.hpp"
#include "headers/moveGenerator.hpp"

class HumanPlayer : public Player
{
public:
    HumanPlayer() = default;
    void PickupPiece(int mouseX, int mouseY) override;
    void DropPiece(int mouseX, int mouseY) override;

private:
    void ReturnHeldPiece();
    bool IsOutOfBounds(int x, int y);
    int GetTileFromMouse(int mouseX, int mouseY);
};