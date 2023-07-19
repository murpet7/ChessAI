#include "headers/moveGenerator.hpp"

std::list<Move> GenerateAllMoves(Board board, int playerToMove, int pawnTwoSquareFile)
{
    std::list<Move> pseudoLegalMoves;
    std::list<int> squares = board.pieceSquaresOfType[PAWN | playerToMove];
    for (int square : squares)
        GeneratePawnMoves(board.pieces, square, playerToMove, pseudoLegalMoves, pawnTwoSquareFile);

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

std::list<Move> GenerateMovesForPiece(int pieces[], int square, int heldPiece, int playerToMove, int pawnTwoSquareFile)
{
    std::list<Move> pseudoLegalMoves;
    switch (heldPiece - playerToMove)
    {
    case PAWN:
        GeneratePawnMoves(pieces, square, playerToMove, pseudoLegalMoves, pawnTwoSquareFile);
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

Move MoveFromStartAndEnd(int from, int to, int playerToMove, int pieces[], int heldPiece, int pawnTwoSquareFile)
{
    std::list<Move> pseudoLegalMoves = GenerateMovesForPiece(pieces, from, heldPiece, playerToMove, pawnTwoSquareFile);
    for (Move pseudoLegalMove : pseudoLegalMoves)
    {
        if (pseudoLegalMove.GetTo() == to)
            return pseudoLegalMove;
    }
    return Move();
}

void GeneratePawnMoves(int pieces[], int square, int playerToMove, std::list<Move> &pseudoLegalMoves, int pawnTwoSquareFile)
{
    // Add promotion
    bool isWhite = playerToMove == WHITE;
    int direction = isWhite ? -8 : 8;
    int forwardSquare = square + direction;
    int squareRank = RankIndex(square);
    int squareFile = FileIndex(square);
    if (pieces[forwardSquare] == NONE)
    {
        pseudoLegalMoves.push_back(Move(square, forwardSquare));
        if ((isWhite && squareRank == 6) || (!isWhite && squareRank == 1))
        {
            int doubleForwardSquare = forwardSquare + direction;
            if (pieces[doubleForwardSquare] == NONE)
            {
                pseudoLegalMoves.push_back(Move(square, doubleForwardSquare, PAWN_TWO_SQUARES));
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
    if ((isWhite && squareRank == 3) || (!isWhite && squareRank == 4))
    {
        if (pawnTwoSquareFile == squareFile - 1)
        {
            pseudoLegalMoves.push_back(Move(square, leftCaptureSquare, EN_PASSANT));
        }
        if (pawnTwoSquareFile == squareFile + 1)
        {
            pseudoLegalMoves.push_back(Move(square, rightCaptureSquare, EN_PASSANT));
        }
    }
}

void GenerateKnightMoves(int pieces[], int square, int playerToMove, std::list<Move> &pseudoLegalMoves)
{
    int directions[8] = {-17, -15, -10, -6, 6, 10, 15, 17};
    int deltaFiles[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
    int deltaRanks[8] = {-2, -2, -1, -1, 1, 1, 2, 2};

    for (int i = 0; i < 8; i++)
    {
        int newSquare = square + directions[i];
        if (IsOutOfBounds(square, deltaRanks[i], deltaFiles[i]))
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
    // add castling
    int directions[8] = {-9, -8, -7, -1, 1, 7, 8, 9};
    int deltaRanks[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int deltaFiles[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int i = 0; i < 8; i++)
    {
        int newSquare = square + directions[i];
        if (IsOutOfBounds(square, deltaRanks[i], deltaFiles[i]))
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
        for (int i = 1; i <= NumSquaresToEdge(square, direction); i++)
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

bool IsOutOfBounds(int oldSquare, int deltaRank, int deltaFile)
{
    int oldRank = RankIndex(oldSquare);
    int oldFile = FileIndex(oldSquare);
    if (oldRank + deltaRank < 0 || oldRank + deltaRank > 7 || oldFile + deltaFile < 0 || oldFile + deltaFile > 7)
        return true;
    return false;
}

bool IsCapturableSquare(int pieces[], int square, int playerToMove)
{
    return pieces[square] != NONE && PieceIsColor(pieces[square], playerToMove);
}

bool IsEmptySquare(int pieces[], int square)
{
    return pieces[square] == NONE;
}

bool IsEmptySquareOrCapturable(int pieces[], int square, int playerToMove)
{
    return pieces[square] == NONE || PieceIsColor(pieces[square], playerToMove);
}

int NumSquaresToEdge(int square, int direction)
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