#include "headers/board.hpp"

Board::Board()
{
    PiecesFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
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
            int squareIndex = SquareIndex(file, rank);
            int pieceType = PieceTypeFromChar(FEN[i]);
            std::list<int> &indices = pieceSquaresOfType[pieceType];
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

bool Board::CanCastleKingside(int playerToMove)
{
    if (playerToMove == WHITE)
        return castleMask & whiteCastleKingsideMask;
    else
        return castleMask & blackCastleKingsideMask;
}

bool Board::CanCastleQueenside(int playerToMove)
{
    if (playerToMove == WHITE)
        return castleMask & whiteCastleQueensideMask;
    else
        return castleMask & blackCastleQueensideMask;
}

void Board::RemoveKingsideCastle(int playerToMove)
{
    if (playerToMove == WHITE)
        castleMask &= ~whiteCastleKingsideMask;
    else
        castleMask &= ~blackCastleKingsideMask;
}

void Board::RemoveQueensideCastle(int playerToMove)
{
    if (playerToMove == WHITE)
        castleMask &= ~whiteCastleQueensideMask;
    else
        castleMask &= ~blackCastleQueensideMask;
}
