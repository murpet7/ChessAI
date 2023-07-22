#include "headers/moveGenerator.hpp"

std::vector<Move> GenerateAllPseudoLegalMoves(Board board, int colorToMove, int pawnTwoSquareFile)
{
    std::vector<Move> pseudoLegalMoves;
    std::vector<int> squares = board.pieceSquaresOfType[PAWN | colorToMove];
    for (int square : squares)
        GeneratePawnMoves(board.pieces, square, colorToMove, pseudoLegalMoves, pawnTwoSquareFile);

    squares = board.pieceSquaresOfType[KNIGHT | colorToMove];
    for (int square : squares)
        GenerateKnightMoves(board.pieces, square, colorToMove, pseudoLegalMoves);

    squares = board.pieceSquaresOfType[BISHOP | colorToMove];
    for (int square : squares)
        GenerateBishopMoves(board.pieces, square, colorToMove, pseudoLegalMoves);

    squares = board.pieceSquaresOfType[ROOK | colorToMove];
    for (int square : squares)
        GenerateRookMoves(board.pieces, square, colorToMove, pseudoLegalMoves);

    squares = board.pieceSquaresOfType[QUEEN | colorToMove];
    for (int square : squares)
        GenerateQueenMoves(board.pieces, square, colorToMove, pseudoLegalMoves);

    squares = board.pieceSquaresOfType[KING | colorToMove];
    for (int square : squares)
        GenerateKingMoves(board.pieces, square, colorToMove, board, pseudoLegalMoves);
    return pseudoLegalMoves;
}

std::vector<Move> GenerateAllLegalMoves(Board board, int colorToMove, int pawnTwoSquareFile)
{
    std::vector<Move> pseudoLegalMoves = GenerateAllPseudoLegalMoves(board, colorToMove, pawnTwoSquareFile);
    std::vector<Move> legalMoves = FilterOnCheck(pseudoLegalMoves, board, colorToMove);
    return legalMoves;
}

std::vector<Move> GenerateMovesForPiece(int pieces[], int square, int heldPiece, int colorToMove, int pawnTwoSquareFile, Board board)
{
    std::vector<Move> pseudoLegalMoves;
    switch (heldPiece - colorToMove)
    {
    case PAWN:
        GeneratePawnMoves(pieces, square, colorToMove, pseudoLegalMoves, pawnTwoSquareFile);
        break;
    case KNIGHT:
        GenerateKnightMoves(pieces, square, colorToMove, pseudoLegalMoves);
        break;
    case BISHOP:
        GenerateBishopMoves(pieces, square, colorToMove, pseudoLegalMoves);
        break;
    case ROOK:
        GenerateRookMoves(pieces, square, colorToMove, pseudoLegalMoves);
        break;
    case QUEEN:
        GenerateQueenMoves(pieces, square, colorToMove, pseudoLegalMoves);
        break;
    case KING:
        GenerateKingMoves(pieces, square, colorToMove, board, pseudoLegalMoves);
        break;
    default:
        break;
    }
    std::vector<Move> legalMoves = FilterOnCheck(pseudoLegalMoves, board, colorToMove);
    return legalMoves;
}

Move ToMove(int from, int to, int colorToMove, int pieces[], int heldPiece, int pawnTwoSquareFile, Board board)
{
    std::vector<Move> pseudoLegalMoves = GenerateMovesForPiece(pieces, from, heldPiece, colorToMove, pawnTwoSquareFile, board);
    for (Move pseudoLegalMove : pseudoLegalMoves)
    {
        if (pseudoLegalMove.GetTo() == to)
            return pseudoLegalMove;
    }
    return Move();
}

std::vector<Move> FilterOnCheck(std::vector<Move> pseudoLegalMoves, Board board, int colorToMove)
{
    std::vector<Move> legalMoves;
    int otherPlayer = colorToMove == WHITE ? BLACK : WHITE;

    for (Move pseudoLegalMove : pseudoLegalMoves)
    {
        Board newBoard = board;
        newBoard.MovePiece(pseudoLegalMove);
        int kingSquare = newBoard.pieceSquaresOfType[KING | colorToMove].front();
        std::vector<Move> otherPlayerMoves = GenerateAllPseudoLegalMoves(newBoard, otherPlayer, newBoard.pawnTwoSquareFile);
        if (pseudoLegalMove.GetFlag() == CASTLE)
        {
            int passThroughSquare = FileIndex(pseudoLegalMove.GetTo()) == 2 ? kingSquare + 1 : kingSquare - 1;
            if (IsSquareAttacked(passThroughSquare, otherPlayerMoves))
                continue;
        }
        if (!IsSquareAttacked(kingSquare, otherPlayerMoves))
        {
            legalMoves.push_back(pseudoLegalMove);
        }
    }
    return legalMoves;
}

void GeneratePawnMoves(int pieces[], int square, int colorToMove, std::vector<Move> &pseudoLegalMoves, int pawnTwoSquareFile)
{
    bool isWhite = colorToMove == WHITE;
    int direction = isWhite ? -8 : 8;
    int forwardSquare = square + direction;
    int squareRank = RankIndex(square);
    int squareFile = FileIndex(square);
    int forwardSquareRank = RankIndex(forwardSquare);
    if (pieces[forwardSquare] == NONE)
    {
        if (forwardSquareRank == 0 || forwardSquareRank == 7)
        {
            AddPromotions(square, forwardSquare, pseudoLegalMoves);
        }
        else
        {
            pseudoLegalMoves.push_back(Move(square, forwardSquare));
        }
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
    if (RankIndex(leftCaptureSquare) == RankIndex(forwardSquare) && IsCapturableSquare(pieces, leftCaptureSquare, colorToMove))
    {
        if (forwardSquareRank == 0 || forwardSquareRank == 7)
        {
            AddPromotions(square, leftCaptureSquare, pseudoLegalMoves);
        }
        else
        {
            pseudoLegalMoves.push_back(Move(square, leftCaptureSquare));
        }
    }
    int rightCaptureSquare = forwardSquare + 1;
    if (RankIndex(rightCaptureSquare) == RankIndex(forwardSquare) && IsCapturableSquare(pieces, rightCaptureSquare, colorToMove))
    {
        if (forwardSquareRank == 0 || forwardSquareRank == 7)
        {
            AddPromotions(square, rightCaptureSquare, pseudoLegalMoves);
        }
        else
        {
            pseudoLegalMoves.push_back(Move(square, rightCaptureSquare));
        }
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

void GenerateKnightMoves(int pieces[], int square, int colorToMove, std::vector<Move> &pseudoLegalMoves)
{
    int directions[8] = {-17, -15, -10, -6, 6, 10, 15, 17};
    int deltaFiles[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
    int deltaRanks[8] = {-2, -2, -1, -1, 1, 1, 2, 2};

    for (int i = 0; i < 8; i++)
    {
        int newSquare = square + directions[i];
        if (IsOutOfBounds(square, deltaRanks[i], deltaFiles[i]))
            continue;
        if (IsEmptySquareOrCapturable(pieces, newSquare, colorToMove))
        {
            pseudoLegalMoves.push_back(Move(square, newSquare));
        }
    }
}

void GenerateBishopMoves(int pieces[], int square, int colorToMove, std::vector<Move> &pseudoLegalMoves)
{
    std::vector<int> directions = {NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST};
    GenerateSlidingMoves(pieces, square, colorToMove, directions, pseudoLegalMoves);
}

void GenerateRookMoves(int pieces[], int square, int colorToMove, std::vector<Move> &pseudoLegalMoves)
{
    std::vector<int> directions = {NORTH, EAST, SOUTH, WEST};
    GenerateSlidingMoves(pieces, square, colorToMove, directions, pseudoLegalMoves);
}

void GenerateQueenMoves(int pieces[], int square, int colorToMove, std::vector<Move> &pseudoLegalMoves)
{
    std::vector<int> directions = {NORTH, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST};
    GenerateSlidingMoves(pieces, square, colorToMove, directions, pseudoLegalMoves);
}

void GenerateKingMoves(int pieces[], int square, int colorToMove, Board board, std::vector<Move> &pseudoLegalMoves)
{
    int directions[8] = {-9, -8, -7, -1, 1, 7, 8, 9};
    int deltaRanks[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int deltaFiles[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int i = 0; i < 8; i++)
    {
        int newSquare = square + directions[i];
        if (IsOutOfBounds(square, deltaRanks[i], deltaFiles[i]))
            continue;
        if (IsEmptySquareOrCapturable(pieces, newSquare, colorToMove))
        {
            pseudoLegalMoves.push_back(Move(square, newSquare));
        }
    }
    if (board.CanCastleKingside(colorToMove))
    {
        if (IsEmptySquare(pieces, square + 1) && IsEmptySquare(pieces, square + 2))
        {
            pseudoLegalMoves.push_back(Move(square, square + 2, CASTLE));
        }
    }
    if (board.CanCastleQueenside(colorToMove))
    {
        if (IsEmptySquare(pieces, square - 1) && IsEmptySquare(pieces, square - 2) && IsEmptySquare(pieces, square - 3))
        {
            pseudoLegalMoves.push_back(Move(square, square - 2, CASTLE));
        }
    }
}

void GenerateSlidingMoves(int pieces[], int square, int colorToMove, std::vector<int> directions, std::vector<Move> &pseudoLegalMoves)
{
    for (int direction : directions)
    {
        for (int i = 1; i <= NumSquaresToEdge(square, direction); i++)
        {
            int newSquare = square + i * direction;
            if (!IsEmptySquare(pieces, newSquare))
            {
                if (IsCapturableSquare(pieces, newSquare, colorToMove))
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

bool IsCapturableSquare(int pieces[], int square, int colorToMove)
{
    return pieces[square] != NONE && PieceIsColor(pieces[square], colorToMove);
}

bool IsEmptySquare(int pieces[], int square)
{
    return pieces[square] == NONE;
}

bool IsEmptySquareOrCapturable(int pieces[], int square, int colorToMove)
{
    return pieces[square] == NONE || PieceIsColor(pieces[square], colorToMove);
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

bool IsSquareAttacked(int square, std::vector<Move> moves)
{
    for (Move move : moves)
    {
        if (move.GetTo() == square)
        {
            return true;
        }
    }
    return false;
}

void AddPromotions(int from, int to, std::vector<Move> &pseudoLegalMoves)
{
    pseudoLegalMoves.push_back(Move(from, to, QUEEN_PROMOTION));
    pseudoLegalMoves.push_back(Move(from, to, ROOK_PROMOTION));
    pseudoLegalMoves.push_back(Move(from, to, BISHOP_PROMOTION));
    pseudoLegalMoves.push_back(Move(from, to, KNIGHT_PROMOTION));
}