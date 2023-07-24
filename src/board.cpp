#include "headers/board.hpp"
#include "headers/moveGenerator.hpp"

Board::Board()
{
    PiecesFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

void Board::MovePiece(Move move)
{
    int to = move.GetTo();
    int from = move.GetFrom();

    int pieceType = pieces[from];
    int colorToMove = GetPieceColor(pieceType);
    CheckCastleRights(pieceType, from);

    int capturedPiece = pieces[to];
    if (capturedPiece != NONE)
    {
        std::vector<int> &indices = pieceSquaresOfType[capturedPiece];
        indices.erase(std::remove(indices.begin(), indices.end(), to), indices.end());
    }
    std::vector<int> &indices = pieceSquaresOfType[pieceType];
    pieces[from] = NONE;
    indices.erase(std::remove(indices.begin(), indices.end(), from), indices.end());
    pieces[to] = pieceType;
    indices.push_back(to);

    int flag = move.GetFlag();
    if (flag == PAWN_TWO_SQUARES)
        pawnTwoSquareFile = File(to);
    else
        pawnTwoSquareFile = -2;

    if (flag == EN_PASSANT)
    {
        int captureSquare = Square(File(to), Rank(from));
        pieces[captureSquare] = NONE;
    }

    if (flag == CASTLE)
    {
        if (File(to) == 2)
        {
            Castle(to - 2, to + 1);
        }
        else
        {
            Castle(to + 1, to - 1);
        }
    }

    if (flag == QUEEN_PROMOTION)
    {
        Promote(QUEEN, to);
    }
    else if (flag == ROOK_PROMOTION)
    {
        Promote(ROOK, to);
    }
    else if (flag == BISHOP_PROMOTION)
    {
        Promote(BISHOP, to);
    }
    else if (flag == KNIGHT_PROMOTION)
    {
        Promote(KNIGHT, to);
    }
    FinishTurn();
}

void Board::Castle(int oldRookPos, int newRookPos)
{
    int pieceType = ROOK | colorToMove;

    pieces[oldRookPos] = NONE;
    std::vector<int> &indices = pieceSquaresOfType[pieceType];
    indices.erase(std::remove(indices.begin(), indices.end(), oldRookPos), indices.end());

    pieces[newRookPos] = pieceType;
    indices.push_back(newRookPos);
}

void Board::CheckCastleRights(int pieceType, int square)
{
    if (pieceType == (KING | colorToMove))
    {
        RemoveKingsideCastle(colorToMove);
        RemoveQueensideCastle(colorToMove);
    }
    if (pieceType == (ROOK | colorToMove))
    {
        if (File(square) == 0)
        {
            RemoveQueensideCastle(colorToMove);
        }
        else if (File(square) == 7)
        {
            RemoveKingsideCastle(colorToMove);
        }
    }
}

void Board::Promote(int promotionType, int square)
{
    pieces[square] = promotionType | colorToMove;
    std::vector<int> &pawnIndices = pieceSquaresOfType[PAWN | colorToMove];
    std::vector<int> &promotionIndices = pieceSquaresOfType[promotionType | colorToMove];
    pawnIndices.erase(std::remove(pawnIndices.begin(), pawnIndices.end(), square), pawnIndices.end());
    promotionIndices.push_back(square);
}

void Board::FinishTurn()
{
    if (colorToMove == WHITE)
        colorToMove = BLACK;
    else
        colorToMove = WHITE;
}

void Board::PiecesFromFEN(std::string FEN)
{
    int file = 0;
    int rank = 0;
    for (int i = 0; i < FEN.length(); i++)
    {
        if (FEN[i] == '/')
        {
            file = 0;
            rank++;
            continue;
        }
        if (FEN[i] >= '1' && FEN[i] <= '8')
        {
            file += FEN[i] - '0';
        }
        else
        {
            int squareIndex = Square(file, rank);
            int pieceType = PieceTypeFromChar(FEN[i]);
            std::vector<int> &indices = pieceSquaresOfType[pieceType];
            indices.push_back(squareIndex);
            pieces[squareIndex] = pieceType;
            file++;
        }
    }
}

int Board::PieceTypeFromChar(char c)
{
    int pieceType = NONE;
    switch (c)
    {
    case 'p':
        pieceType = BLACK | PAWN;
        break;
    case 'n':
        pieceType = BLACK | KNIGHT;
        break;
    case 'b':
        pieceType = BLACK | BISHOP;
        break;
    case 'r':
        pieceType = BLACK | ROOK;
        break;
    case 'q':
        pieceType = BLACK | QUEEN;
        break;
    case 'k':
        pieceType = BLACK | KING;
        break;
    case 'P':
        pieceType = WHITE | PAWN;
        break;
    case 'N':
        pieceType = WHITE | KNIGHT;
        break;
    case 'B':
        pieceType = WHITE | BISHOP;
        break;
    case 'R':
        pieceType = WHITE | ROOK;
        break;
    case 'Q':
        pieceType = WHITE | QUEEN;
        break;
    case 'K':
        pieceType = WHITE | KING;
        break;
    }
    return pieceType;
}

bool Board::CanCastleKingside(int colorToMove, int castleMask)
{
    if (colorToMove == WHITE)
        return castleMask & WHITE_CASTLE_KINGSIDE_MASK;
    else
        return castleMask & BLACK_CASTLE_KINGSIDE_MASK;
}

bool Board::CanCastleQueenside(int colorToMove, int castleMask)
{
    if (colorToMove == WHITE)
        return castleMask & WHITE_CASTLE_QUEENSIDE_MASK;
    else
        return castleMask & BLACK_CASTLE_QUEENSIDE_MASK;
}

void Board::RemoveKingsideCastle(int colorToMove)
{
    if (colorToMove == WHITE)
        castleMask &= ~WHITE_CASTLE_KINGSIDE_MASK;
    else
        castleMask &= ~BLACK_CASTLE_KINGSIDE_MASK;
}

void Board::RemoveQueensideCastle(int colorToMove)
{
    if (colorToMove == WHITE)
        castleMask &= ~WHITE_CASTLE_QUEENSIDE_MASK;
    else
        castleMask &= ~BLACK_CASTLE_QUEENSIDE_MASK;
}

int Board::GetKingSquare(int color)
{
    return pieceSquaresOfType[KING | color].front();
}
