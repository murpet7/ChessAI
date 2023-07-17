#include "headers/board.hpp"

Board::Board()
{
    PiecesFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

void Board::PiecesFromFEN(std::string FEN)
{
    int x = 0;
    int y = 0;
    for (int i = 0; i < FEN.length(); i++)
    {
        if (FEN[i] == '/')
        {
            x = 0;
            y++;
            continue;
        }
        if (FEN[i] >= '1' && FEN[i] <= '8')
        {
            x += FEN[i] - '0';
        }
        else
        {
            switch (FEN[i])
            {
            case 'p':
                pieces[SquareIndex(x, y)] = BLACK | PAWN;
                break;
            case 'n':
                pieces[SquareIndex(x, y)] = BLACK | KNIGHT;
                break;
            case 'b':
                pieces[SquareIndex(x, y)] = BLACK | BISHOP;
                break;
            case 'r':
                pieces[SquareIndex(x, y)] = BLACK | ROOK;
                break;
            case 'q':
                pieces[SquareIndex(x, y)] = BLACK | QUEEN;
                break;
            case 'k':
                pieces[SquareIndex(x, y)] = BLACK | KING;
                break;
            case 'P':
                pieces[SquareIndex(x, y)] = WHITE | PAWN;
                break;
            case 'N':
                pieces[SquareIndex(x, y)] = WHITE | KNIGHT;
                break;
            case 'B':
                pieces[SquareIndex(x, y)] = WHITE | BISHOP;
                break;
            case 'R':
                pieces[SquareIndex(x, y)] = WHITE | ROOK;
                break;
            case 'Q':
                pieces[SquareIndex(x, y)] = WHITE | QUEEN;
                break;
            case 'K':
                pieces[SquareIndex(x, y)] = WHITE | KING;
                break;
            }
            x++;
        }
    }
}