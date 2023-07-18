#include "headers/moveGenerator.hpp"

std::list<Move> GenerateAllMoves(Board board, int playerToMove)
{
    std::list<Move> pseudoLegalMoves;
    std::list<int> squares = board.pieceSquaresOfType[PAWN | playerToMove];
    for (int square : squares)
        GeneratePawnMoves(board.pieces, square, playerToMove, pseudoLegalMoves);

    squares = board.pieceSquaresOfType[KNIGHT | playerToMove];
    for (int square : squares)
        GenerateKnightMoves(board.pieces, square, playerToMove, pseudoLegalMoves);

    squares = board.pieceSquaresOfType[BISHOP | playerToMove];
    for (int square : squares)
        GenerateBishopMoves(board.pieces, square, playerToMove, pseudoLegalMoves);

    squares = board.pieceSquaresOfType[ROOK | playerToMove];
    for (int square : squares)
        GenerateRookMoves(board.pieces, square, playerToMove, pseudoLegalMoves);

    squares = board.pieceSquaresOfType[QUEEN | playerToMove];
    for (int square : squares)
        GenerateQueenMoves(board.pieces, square, playerToMove, pseudoLegalMoves);

    squares = board.pieceSquaresOfType[KING | playerToMove];
    for (int square : squares)
        GenerateKingMoves(board.pieces, square, playerToMove, pseudoLegalMoves);
    return pseudoLegalMoves;
}

std::list<Move> GenerateMovesForPiece(int pieces[], int square, int playerToMove)
{
    std::list<Move> pseudoLegalMoves;
    int piece = pieces[square];
    switch (piece)
    {
    case PAWN:
        GeneratePawnMoves(pieces, square, playerToMove, pseudoLegalMoves);
        break;
    case KNIGHT:
        GenerateKnightMoves(pieces, square, playerToMove, pseudoLegalMoves);
        break;
    case BISHOP:
        GenerateBishopMoves(pieces, square, playerToMove, pseudoLegalMoves);
        break;
    case ROOK:
        GenerateRookMoves(pieces, square, playerToMove, pseudoLegalMoves);
        break;
    case QUEEN:
        GenerateQueenMoves(pieces, square, playerToMove, pseudoLegalMoves);
        break;
    case KING:
        GenerateKingMoves(pieces, square, playerToMove, pseudoLegalMoves);
        break;
    default:
        break;
    }
    return pseudoLegalMoves;
}

bool IsLegalMove(Move move, int playerToMove, int pieces[])
{
    std::list<Move> pseudoLegalMoves = GenerateMovesForPiece(pieces, move.from, playerToMove);
    for (Move pseudoLegalMove : pseudoLegalMoves)
    {
        if (pseudoLegalMove.to == move.to)
            return true;
    }
    return false;
}

void GeneratePawnMoves(int pieces[], int square, int playerToMove, std::list<Move> &pseudoLegalMoves)
{
    // Add en passant en promotion
    bool isWhite = playerToMove == WHITE;
    int direction = isWhite ? -8 : 8;
    int forwardSquare = square + direction;
    if (pieces[forwardSquare] == NONE)
    {
        pseudoLegalMoves.push_back(Move(square, forwardSquare));
        if ((isWhite && RankIndex(square) == 6) || (!isWhite && RankIndex(square) == 1))
        {
            int doubleForwardSquare = forwardSquare + direction;
            if (pieces[doubleForwardSquare] == NONE)
            {
                pseudoLegalMoves.push_back(Move(square, doubleForwardSquare));
            }
        }
    }
    int leftCaptureSquare = forwardSquare - 1;
    if (RankIndex(leftCaptureSquare) == RankIndex(forwardSquare) && IsCapturableSquare(pieces, leftCaptureSquare, playerToMove))
    {
        pseudoLegalMoves.push_back(Move(square, leftCaptureSquare));
    }
    int rightCaptureSquare = forwardSquare + 1;
    if (RankIndex(rightCaptureSquare) == RankIndex(forwardSquare) && IsCapturableSquare(pieces, rightCaptureSquare, playerToMove))
    {
        pseudoLegalMoves.push_back(Move(square, rightCaptureSquare));
    }
}

void GenerateKnightMoves(int pieces[], int square, int playerToMove, std::list<Move> &pseudoLegalMoves)
{
    int directions[8] = {-17, -15, -10, -6, 6, 10, 15, 17};
    for (int direction : directions)
    {
        int newSquare = square + direction;
        if (IsOutOfBounds(square, newSquare))
            continue;
        if (IsEmptySquareOrCapturable(pieces, newSquare, playerToMove))
        {
            pseudoLegalMoves.push_back(Move(square, newSquare));
        }
    }
}

void GenerateBishopMoves(int pieces[], int square, int playerToMove, std::list<Move> &pseudoLegalMoves)
{
    std::list<int> directions = {NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST};
    GenerateSlidingMoves(pieces, square, playerToMove, directions, pseudoLegalMoves);
}

void GenerateRookMoves(int pieces[], int square, int playerToMove, std::list<Move> &pseudoLegalMoves)
{
    std::list<int> directions = {NORTH, EAST, SOUTH, WEST};
    GenerateSlidingMoves(pieces, square, playerToMove, directions, pseudoLegalMoves);
}

void GenerateQueenMoves(int pieces[], int square, int playerToMove, std::list<Move> &pseudoLegalMoves)
{
    std::list<int> directions = {NORTH, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST};
    GenerateSlidingMoves(pieces, square, playerToMove, directions, pseudoLegalMoves);
}

void GenerateKingMoves(int pieces[], int square, int playerToMove, std::list<Move> &pseudoLegalMoves)
{
    std::list<int> directions = {-9, -8, -7, -1, 1, 7, 8, 9};
    for (int direction : directions)
    {
        int newSquare = square + direction;
        if (IsOutOfBounds(square, newSquare))
            continue;
        if (IsEmptySquareOrCapturable(pieces, newSquare, playerToMove))
        {
            pseudoLegalMoves.push_back(Move(square, newSquare));
        }
    }
}

void GenerateSlidingMoves(int pieces[], int square, int playerToMove, std::list<int> directions, std::list<Move> &pseudoLegalMoves)
{
    for (int direction : directions)
    {
        for (int i = 1; i < NumSquaresToEdge(square, direction); i++)
        {
            int newSquare = square + i * direction;
            if (!IsEmptySquare(pieces, newSquare))
            {
                if (IsCapturableSquare(pieces, newSquare, playerToMove))
                {
                    pseudoLegalMoves.push_back(Move(square, newSquare));
                }
                break;
            }
            pseudoLegalMoves.push_back(Move(square, newSquare));
        }
    }
}

bool IsOutOfBounds(int oldSquare, int newSquare)
{
    int delta = newSquare - oldSquare;
    int oldRank = RankIndex(oldSquare);
    int oldFile = FileIndex(oldSquare);
    int deltaRank = delta / 8;
    int deltaFile = delta % 8;
    if (oldRank - deltaRank < 0 || oldRank - deltaRank > 7 || oldFile - deltaFile < 0 || oldFile - deltaFile > 7)
        return true;
    return false;
}

bool IsCapturableSquare(int pieces[], int square, int playerToMove)
{
    return pieces[square] != NONE && (pieces[square] & WHITE) != playerToMove;
}

bool IsEmptySquare(int pieces[], int square)
{
    return pieces[square] == NONE;
}

bool IsEmptySquareOrCapturable(int pieces[], int square, int playerToMove)
{
    return pieces[square] == NONE || (pieces[square] & WHITE) != playerToMove;
}

bool NumSquaresToEdge(int square, int direction)
{
    int rank = RankIndex(square);
    int file = FileIndex(square);
    switch (direction)
    {
    case NORTH:
        return rank;
    case NORTH_EAST:
        return std::min(rank, 7 - file);
    case EAST:
        return 7 - file;
    case SOUTH_EAST:
        return std::min(7 - rank, 7 - file);
    case SOUTH:
        return 7 - rank;
    case SOUTH_WEST:
        return std::min(7 - rank, file);
    case WEST:
        return file;
    case NORTH_WEST:
        return std::min(rank, file);
    default:
        return 0;
    }
}