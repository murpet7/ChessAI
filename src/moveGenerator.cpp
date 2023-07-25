#include "headers/moveGenerator.hpp"

std::vector<Move> MoveGenerator::GenerateAllPseudoLegalMoves(std::map<int, std::vector<int>> pieceSquaresOfType, int pieces[], int colorToMove, int pawnTwoSquareFile, int castleMask)
{
    std::vector<Move> pseudoLegalMoves;
    for (int square : pieceSquaresOfType[PAWN | colorToMove])
        GeneratePawnMoves(pieces, square, colorToMove, pawnTwoSquareFile, pseudoLegalMoves);

    for (int square : pieceSquaresOfType[KNIGHT | colorToMove])
        GenerateKnightMoves(pieces, square, colorToMove, pseudoLegalMoves);

    for (int square : pieceSquaresOfType[BISHOP | colorToMove])
        GenerateBishopMoves(pieces, square, colorToMove, pseudoLegalMoves);

    for (int square : pieceSquaresOfType[ROOK | colorToMove])
        GenerateRookMoves(pieces, square, colorToMove, pseudoLegalMoves);

    for (int square : pieceSquaresOfType[QUEEN | colorToMove])
        GenerateQueenMoves(pieces, square, colorToMove, pseudoLegalMoves);

    for (int square : pieceSquaresOfType[KING | colorToMove])
        GenerateKingMoves(pieces, square, colorToMove, castleMask, pseudoLegalMoves);
    return pseudoLegalMoves;
}

std::vector<Move> MoveGenerator::GenerateAllLegalMoves(Board board)
{
    std::vector<Move> pseudoLegalMoves = GenerateAllPseudoLegalMoves(board.pieceSquaresOfType, board.pieces, board.colorToMove, board.pawnTwoSquareFile, board.castleMask);
    std::vector<Move> legalMoves = FilterOnCheck(board, pseudoLegalMoves);
    return legalMoves;
}

std::vector<Move> MoveGenerator::GenerateMovesForPiece(Board board, int square, int heldPiece)
{
    int colorToMove = board.colorToMove;
    std::vector<Move> pseudoLegalMoves;
    switch (heldPiece - colorToMove)
    {
    case PAWN:
        GeneratePawnMoves(board.pieces, square, colorToMove, board.pawnTwoSquareFile, pseudoLegalMoves);
        break;
    case KNIGHT:
        GenerateKnightMoves(board.pieces, square, colorToMove, pseudoLegalMoves);
        break;
    case BISHOP:
        GenerateBishopMoves(board.pieces, square, colorToMove, pseudoLegalMoves);
        break;
    case ROOK:
        GenerateRookMoves(board.pieces, square, colorToMove, pseudoLegalMoves);
        break;
    case QUEEN:
        GenerateQueenMoves(board.pieces, square, colorToMove, pseudoLegalMoves);
        break;
    case KING:
        GenerateKingMoves(board.pieces, square, colorToMove, board.castleMask, pseudoLegalMoves);
        break;
    default:
        break;
    }
    std::vector<Move> legalMoves = FilterOnCheck(board, pseudoLegalMoves);
    return legalMoves;
}

Move MoveGenerator::MovesquaresToMove(Board board, int from, int to, int heldPiece)
{
    std::vector<Move> pseudoLegalMoves = GenerateMovesForPiece(board, from, heldPiece);
    for (Move pseudoLegalMove : pseudoLegalMoves)
    {
        if (pseudoLegalMove.GetTo() == to)
            return pseudoLegalMove;
    }
    return Move();
}

std::vector<Move> MoveGenerator::FilterOnCheck(Board board, std::vector<Move> pseudoLegalMoves)
{
    std::vector<Move> legalMoves;
    int otherPlayer = board.colorToMove == WHITE ? BLACK : WHITE;

    for (Move pseudoLegalMove : pseudoLegalMoves)
    {
        Board newBoard = board;
        newBoard.MakeMove(pseudoLegalMove);
        int kingSquare = newBoard.pieceSquaresOfType[KING | board.colorToMove].front();
        std::vector<Move> otherPlayerMoves = GenerateAllPseudoLegalMoves(newBoard.pieceSquaresOfType, newBoard.pieces, otherPlayer, newBoard.pawnTwoSquareFile, newBoard.castleMask);

        // Check castle through check
        if (pseudoLegalMove.GetFlag() == CASTLE)
        {
            int passThroughSquare = File(pseudoLegalMove.GetTo()) == 2 ? kingSquare + 1 : kingSquare - 1;
            if (IsSquareAttacked(passThroughSquare, otherPlayerMoves))
                continue;
        }

        // Check king in check
        if (!IsSquareAttacked(kingSquare, otherPlayerMoves))
        {
            legalMoves.push_back(pseudoLegalMove);
        }
    }
    return legalMoves;
}

void MoveGenerator::GeneratePawnMoves(int pieces[], int square, int colorToMove, int pawnTwoSquareFile, std::vector<Move> &pseudoLegalMoves)
{
    bool isWhite = colorToMove == WHITE;
    int direction = isWhite ? -8 : 8;
    int forwardSquare = square + direction;
    int squareRank = Rank(square);
    int squareFile = File(square);
    int forwardSquareRank = Rank(forwardSquare);

    // Forward
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

    // Capture Left
    int leftCaptureSquare = forwardSquare - 1;
    if (Rank(leftCaptureSquare) == Rank(forwardSquare) && IsCapturableSquare(pieces, leftCaptureSquare, colorToMove))
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

    // Capture Right
    int rightCaptureSquare = forwardSquare + 1;
    if (Rank(rightCaptureSquare) == Rank(forwardSquare) && IsCapturableSquare(pieces, rightCaptureSquare, colorToMove))
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

    // En passant
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

void MoveGenerator::GenerateKnightMoves(int pieces[], int square, int colorToMove, std::vector<Move> &pseudoLegalMoves)
{
    int directions[8] = {-17, -15, -10, -6, 6, 10, 15, 17};

    for (int i = 0; i < 8; i++)
    {
        int newSquare = square + directions[i];
        if (IsKnightOutOfBounds(square, newSquare))
            continue;
        if (IsEmptySquareOrCapturable(pieces, newSquare, colorToMove))
        {
            pseudoLegalMoves.push_back(Move(square, newSquare));
        }
    }
}

void MoveGenerator::GenerateBishopMoves(int pieces[], int square, int colorToMove, std::vector<Move> &pseudoLegalMoves)
{
    std::vector<int> directions = {NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST};
    GenerateSlidingMoves(pieces, square, colorToMove, directions, pseudoLegalMoves);
}

void MoveGenerator::GenerateRookMoves(int pieces[], int square, int colorToMove, std::vector<Move> &pseudoLegalMoves)
{
    std::vector<int> directions = {NORTH, EAST, SOUTH, WEST};
    GenerateSlidingMoves(pieces, square, colorToMove, directions, pseudoLegalMoves);
}

void MoveGenerator::GenerateQueenMoves(int pieces[], int square, int colorToMove, std::vector<Move> &pseudoLegalMoves)
{
    std::vector<int> directions = {NORTH, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST};
    GenerateSlidingMoves(pieces, square, colorToMove, directions, pseudoLegalMoves);
}

void MoveGenerator::GenerateKingMoves(int pieces[], int square, int colorToMove, int castleMask, std::vector<Move> &pseudoLegalMoves)
{
    int directions[8] = {-9, -8, -7, -1, 1, 7, 8, 9};
    for (int i = 0; i < 8; i++)
    {
        int newSquare = square + directions[i];
        if (IsKingOutOfBounds(square, newSquare))
            continue;
        if (IsEmptySquareOrCapturable(pieces, newSquare, colorToMove))
        {
            pseudoLegalMoves.push_back(Move(square, newSquare));
        }
    }

    // Castling
    if (Board::CanCastleKingside(colorToMove, castleMask))
    {
        if (IsEmptySquare(pieces, square + 1) && IsEmptySquare(pieces, square + 2))
        {
            pseudoLegalMoves.push_back(Move(square, square + 2, CASTLE));
        }
    }
    if (Board::CanCastleQueenside(colorToMove, castleMask))
    {
        if (IsEmptySquare(pieces, square - 1) && IsEmptySquare(pieces, square - 2) && IsEmptySquare(pieces, square - 3))
        {
            pseudoLegalMoves.push_back(Move(square, square - 2, CASTLE));
        }
    }
}

void MoveGenerator::GenerateSlidingMoves(int pieces[], int square, int colorToMove, std::vector<int> directions, std::vector<Move> &pseudoLegalMoves)
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

bool MoveGenerator::IsKnightOutOfBounds(int oldSquare, int newSquare)
{
    if (newSquare < 0 || newSquare > 63)
        return true;
    return abs(Rank(oldSquare) - Rank(newSquare)) + abs(File(oldSquare) - File(newSquare)) != 3;
}

bool MoveGenerator::IsKingOutOfBounds(int oldSquare, int newSquare)
{
    if (newSquare < 0 || newSquare > 63)
        return true;
    return abs(Rank(oldSquare) - Rank(newSquare)) != 1 && abs(File(oldSquare) - File(newSquare)) != 1;
}

bool MoveGenerator::IsCapturableSquare(int pieces[], int square, int colorToMove)
{
    return pieces[square] != NONE && PieceIsColor(pieces[square], colorToMove);
}

bool MoveGenerator::IsEmptySquare(int pieces[], int square)
{
    return pieces[square] == NONE;
}

bool MoveGenerator::IsEmptySquareOrCapturable(int pieces[], int square, int colorToMove)
{
    return pieces[square] == NONE || PieceIsColor(pieces[square], colorToMove);
}

int MoveGenerator::NumSquaresToEdge(int square, int direction)
{
    int rank = Rank(square);
    int file = File(square);
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

bool MoveGenerator::IsSquareAttacked(int square, std::vector<Move> moves)
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

void MoveGenerator::AddPromotions(int from, int to, std::vector<Move> &pseudoLegalMoves)
{
    pseudoLegalMoves.push_back(Move(from, to, QUEEN_PROMOTION));
    pseudoLegalMoves.push_back(Move(from, to, ROOK_PROMOTION));
    pseudoLegalMoves.push_back(Move(from, to, BISHOP_PROMOTION));
    pseudoLegalMoves.push_back(Move(from, to, KNIGHT_PROMOTION));
}