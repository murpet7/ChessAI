#include "headers/board.hpp"

Board::Board()
{
    PiecesFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

void Board::PiecesFromFEN(std::string FEN)
{
    int rank = 0;
    int file = 0;
    for (int i = 0; i < FEN.length(); i++)
    {
        if (FEN[i] == '/')
        {
            rank = 0;
            file++;
            continue;
        }
        if (FEN[i] >= '1' && FEN[i] <= '8')
        {
            rank += FEN[i] - '0';
        }
        else
        {
            int squareIndex = SquareIndex(rank, file);
            int pieceType = PieceTypeFromChar(FEN[i]);
            std::list<int> &indices = pieceSquaresOfType[pieceType];
            indices.push_back(squareIndex);
            pieces[squareIndex] = pieceType;
            rank++;
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