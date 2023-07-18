#include "headers/move.hpp"

Move::Move()
{
    this->piece = 0;
    this->from = 0;
    this->to = 0;
    this->capturedPiece = 0;
    this->promotedPiece = 0;
    this->flags = 0;
    this->score = 0;
}

Move::Move(int from, int to)
{
    this->piece = 0;
    this->from = from;
    this->to = to;
    this->capturedPiece = 0;
    this->promotedPiece = 0;
    this->flags = 0;
    this->score = 0;
}

Move::Move(int piece, int from, int to, int capturedPiece, int promotedPiece, int flags, int score)
{
    this->piece = piece;
    this->from = from;
    this->to = to;
    this->capturedPiece = capturedPiece;
    this->promotedPiece = promotedPiece;
    this->flags = flags;
    this->score = score;
}