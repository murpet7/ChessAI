#pragma once

class Move
{
public:
    unsigned short moveValue;
    Move();
    Move(int from, int to);
    Move(int from, int to, int flag);
    int GetFrom();
    int GetTo();
    int GetFlag();

private:
    const unsigned short fromMask = 0b0000000000111111;
    const unsigned short toMask = 0b0000111111000000;
    const unsigned short flagMask = 0b1111000000000000;
};

bool IsSameMove(Move move1, Move move2);

enum flags
{
    NORMAL = 0,
    EN_PASSANT = 1,
    CASTLE = 2,
    QUEEN_PROMOTION = 3,
    KNIGHT_PROMOTION = 4,
    ROOK_PROMOTION = 5,
    BISHOP_PROMOTION = 6,
    PAWN_TWO_SQUARES = 7
};