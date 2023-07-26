#include "headers/moveGenerator.hpp"

std::vector<Move> MoveGenerator::GenerateAllPseudoLegalMoves(Board &board)
{
    std::vector<Move> pseudoLegalMoves;
    int colorToMove = board.colorToMove;
    for (int square : board.pieceSquaresOfType[PAWN | board.colorToMove])
        GeneratePawnMoves(board, square, pseudoLegalMoves);

    for (int square : board.pieceSquaresOfType[KNIGHT | colorToMove])
        GenerateKnightMoves(board, square, pseudoLegalMoves);

    for (int square : board.pieceSquaresOfType[BISHOP | colorToMove])
        GenerateBishopMoves(board, square, pseudoLegalMoves);

    for (int square : board.pieceSquaresOfType[ROOK | colorToMove])
        GenerateRookMoves(board, square, pseudoLegalMoves);

    for (int square : board.pieceSquaresOfType[QUEEN | colorToMove])
        GenerateQueenMoves(board, square, pseudoLegalMoves);

    for (int square : board.pieceSquaresOfType[KING | colorToMove])
        GenerateKingMoves(board, square, pseudoLegalMoves);
    return pseudoLegalMoves;
}

std::vector<Move> MoveGenerator::GenerateAllLegalMoves(Board &board)
{
    std::vector<Move> pseudoLegalMoves = GenerateAllPseudoLegalMoves(board);
    std::vector<Move> legalMoves = FilterOnCheck(board, pseudoLegalMoves);
    return legalMoves;
}

std::vector<Move> MoveGenerator::GenerateMovesForPiece(Board &board, int square, int heldPiece)
{
    int colorToMove = board.colorToMove;
    std::vector<Move> pseudoLegalMoves;
    switch (heldPiece - colorToMove)
    {
    case PAWN:
        GeneratePawnMoves(board, square, pseudoLegalMoves);
        break;
    case KNIGHT:
        GenerateKnightMoves(board, square, pseudoLegalMoves);
        break;
    case BISHOP:
        GenerateBishopMoves(board, square, pseudoLegalMoves);
        break;
    case ROOK:
        GenerateRookMoves(board, square, pseudoLegalMoves);
        break;
    case QUEEN:
        GenerateQueenMoves(board, square, pseudoLegalMoves);
        break;
    case KING:
        GenerateKingMoves(board, square, pseudoLegalMoves);
        break;
    default:
        break;
    }
    std::vector<Move> legalMoves = FilterOnCheck(board, pseudoLegalMoves);
    return legalMoves;
}

Move MoveGenerator::MovesquaresToMove(Board &board, int from, int to, int heldPiece)
{
    std::vector<Move> pseudoLegalMoves = GenerateMovesForPiece(board, from, heldPiece);
    for (Move pseudoLegalMove : pseudoLegalMoves)
    {
        if (pseudoLegalMove.GetTo() == to)
            return pseudoLegalMove;
    }
    return Move();
}

std::vector<Move> MoveGenerator::FilterOnCheck(Board &board, std::vector<Move> pseudoLegalMoves)
{
    std::vector<Move> legalMoves;
    int otherPlayer = board.colorToMove == WHITE ? BLACK : WHITE;

    for (Move pseudoLegalMove : pseudoLegalMoves)
    {
        Board newBoard = board;
        newBoard.MakeMove(pseudoLegalMove);
        int kingSquare = newBoard.pieceSquaresOfType[KING | board.colorToMove].front();
        std::vector<Move> otherPlayerMoves = GenerateAllPseudoLegalMoves(newBoard);

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

void MoveGenerator::GeneratePawnMoves(Board &board, int square, std::vector<Move> &pseudoLegalMoves)
{
    bool isWhite = board.colorToMove == WHITE;
    int direction = isWhite ? -8 : 8;
    int forwardSquare = square + direction;
    int squareRank = Rank(square);
    int squareFile = File(square);
    int forwardSquareRank = Rank(forwardSquare);

    // Forward
    if (board.pieces[forwardSquare] == NONE)
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
            if (board.pieces[doubleForwardSquare] == NONE)
            {
                pseudoLegalMoves.push_back(Move(square, doubleForwardSquare, PAWN_TWO_SQUARES));
            }
        }
    }

    // Capture Left
    int leftCaptureSquare = forwardSquare - 1;
    if (Rank(leftCaptureSquare) == Rank(forwardSquare) && IsCapturableSquare(board, leftCaptureSquare))
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
    if (Rank(rightCaptureSquare) == Rank(forwardSquare) && IsCapturableSquare(board, rightCaptureSquare))
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
        if (board.pawnTwoSquareFile == squareFile - 1)
        {
            pseudoLegalMoves.push_back(Move(square, leftCaptureSquare, EN_PASSANT));
        }
        if (board.pawnTwoSquareFile == squareFile + 1)
        {
            pseudoLegalMoves.push_back(Move(square, rightCaptureSquare, EN_PASSANT));
        }
    }
}

void MoveGenerator::GenerateKnightMoves(Board &board, int square, std::vector<Move> &pseudoLegalMoves)
{
    int directions[8] = {-17, -15, -10, -6, 6, 10, 15, 17};

    for (int i = 0; i < 8; i++)
    {
        int newSquare = square + directions[i];
        if (IsKnightOutOfBounds(square, newSquare))
            continue;
        if (IsEmptySquareOrCapturable(board, newSquare))
        {
            pseudoLegalMoves.push_back(Move(square, newSquare));
        }
    }
}

void MoveGenerator::GenerateBishopMoves(Board &board, int square, std::vector<Move> &pseudoLegalMoves)
{
    std::vector<int> directions = {NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST};
    GenerateSlidingMoves(board, square, directions, pseudoLegalMoves);
}

void MoveGenerator::GenerateRookMoves(Board &board, int square, std::vector<Move> &pseudoLegalMoves)
{
    std::vector<int> directions = {NORTH, EAST, SOUTH, WEST};
    GenerateSlidingMoves(board, square, directions, pseudoLegalMoves);
}

void MoveGenerator::GenerateQueenMoves(Board &board, int square, std::vector<Move> &pseudoLegalMoves)
{
    std::vector<int> directions = {NORTH, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST};
    GenerateSlidingMoves(board, square, directions, pseudoLegalMoves);
}

void MoveGenerator::GenerateKingMoves(Board &board, int square, std::vector<Move> &pseudoLegalMoves)
{
    int directions[8] = {-9, -8, -7, -1, 1, 7, 8, 9};
    for (int i = 0; i < 8; i++)
    {
        int newSquare = square + directions[i];
        if (IsKingOutOfBounds(square, newSquare))
            continue;
        if (IsEmptySquareOrCapturable(board, newSquare))
        {
            pseudoLegalMoves.push_back(Move(square, newSquare));
        }
    }

    // Castling
    if (Board::CanCastleKingside(board.colorToMove, board.castleMask))
    {
        if (IsEmptySquare(board, square + 1) && IsEmptySquare(board, square + 2))
        {
            pseudoLegalMoves.push_back(Move(square, square + 2, CASTLE));
        }
    }
    if (Board::CanCastleQueenside(board.colorToMove, board.castleMask))
    {
        if (IsEmptySquare(board, square - 1) && IsEmptySquare(board, square - 2) && IsEmptySquare(board, square - 3))
        {
            pseudoLegalMoves.push_back(Move(square, square - 2, CASTLE));
        }
    }
}

void MoveGenerator::GenerateSlidingMoves(Board &board, int square, std::vector<int> directions, std::vector<Move> &pseudoLegalMoves)
{
    for (int direction : directions)
    {
        for (int i = 1; i <= NumSquaresToEdge(square, direction); i++)
        {
            int newSquare = square + i * direction;
            if (!IsEmptySquare(board, newSquare))
            {
                if (IsCapturableSquare(board, newSquare))
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
    return abs(Rank(oldSquare) - Rank(newSquare)) > 1 || abs(File(oldSquare) - File(newSquare)) > 1;
}

bool MoveGenerator::IsCapturableSquare(Board &board, int square)
{
    return board.pieces[square] != NONE && PieceIsColor(board.pieces[square], board.colorToMove);
}

bool MoveGenerator::IsEmptySquare(Board &board, int square)
{
    return board.pieces[square] == NONE;
}

bool MoveGenerator::IsEmptySquareOrCapturable(Board &board, int square)
{
    return board.pieces[square] == NONE || PieceIsColor(board.pieces[square], board.colorToMove);
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