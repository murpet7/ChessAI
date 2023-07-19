#include "headers/move.hpp"

Move::Move()
{
    moveValue = 0;
}

Move::Move(int from, int to)
{
    moveValue = (unsigned short)(from | to << 6);
}

Move::Move(int from, int to, int flag)
{
    moveValue = (unsigned short)(from | to << 6 | flag << 12);
}

int Move::GetFrom()
{
    return moveValue & fromMask;
}

int Move::GetTo()
{
    return (moveValue & toMask) >> 6;
}

int Move::GetFlag()
{
    return (moveValue & flagMask) >> 12;
}

bool IsSameMove(Move move1, Move move2)
{
    return move1.moveValue == move2.moveValue;
}