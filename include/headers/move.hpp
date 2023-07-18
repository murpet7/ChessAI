#pragma once

class Move
{
public:
    int piece;
    int from;
    int to;
    int capturedPiece;
    int promotedPiece;
    int flags;
    int score;
    Move(int piece, int from, int to, int capturedPiece, int promotedPiece, int flags, int score);
    Move();
    Move(int from, int to);
};

enum flags
{
    NORMAL,
    PAWN_START,
    EN_PASSANT,
    CASTLE,
    CAPTURE,
    PROMOTION
};