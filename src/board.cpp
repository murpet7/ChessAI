#include "headers/board.hpp"
#include "headers/moveGenerator.hpp"

Board::Board()
{
    PiecesFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

int Board::GetTileFromMouse(int mouseX, int mouseY)
{
    if (IsOutOfBounds(mouseX, mouseY))
        return -1;
    int tileX = (mouseX - BOARD_X) / TILE_SIZE;
    int tileY = (mouseY - BOARD_Y) / TILE_SIZE;
    return SquareIndex(tileX, tileY);
}

void Board::PickupPiece(int x, int y)
{
    heldPieceIndex = GetTileFromMouse(x, y);
    heldPiece = pieces[heldPieceIndex];
    pieces[heldPieceIndex] = NONE;
    std::list<int> &indices = pieceSquaresOfType[heldPiece];
    indices.remove(heldPieceIndex);
    if (PieceIsColor(heldPiece, playerToMove) || heldPiece == NONE)
        ReturnHeldPiece();
}

void Board::DropPiece(int x, int y)
{
    if (heldPiece == NONE)
        return;
    int newSquare = GetTileFromMouse(x, y);
    Move move = MoveFromStartAndEnd(heldPieceIndex, newSquare, playerToMove, pieces, heldPiece, pawnTwoSquareFile, *this);
    if (newSquare != -1 && move.moveValue != 0)
    {
        MovePiece(move);
        FinishTurn();
    }
    else
    {
        ReturnHeldPiece();
    }
}

void Board::ReturnHeldPiece()
{
    pieces[heldPieceIndex] = heldPiece;
    std::list<int> &indices = pieceSquaresOfType[heldPiece];
    indices.push_back(heldPieceIndex);
    heldPiece = NONE;
}

void Board::MovePiece(Move move)
{
    int to = move.GetTo();
    int from = move.GetFrom();

    CheckCastleRights(heldPiece, from);

    pieces[to] = heldPiece;
    std::list<int> &indices = pieceSquaresOfType[heldPiece];
    indices.push_back(to);
    heldPiece = NONE;

    int flag = move.GetFlag();
    if (flag == PAWN_TWO_SQUARES)
        pawnTwoSquareFile = FileIndex(to);
    else
        pawnTwoSquareFile = -2;

    if (flag == EN_PASSANT)
    {
        int captureSquare = SquareIndex(FileIndex(to), RankIndex(from));
        pieces[captureSquare] = NONE;
    }

    if (flag == CASTLE)
    {
        if (FileIndex(to) == 2)
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
}

void Board::Castle(int oldRookPos, int newRookPos)
{
    int pieceType = ROOK | playerToMove;

    pieces[oldRookPos] = NONE;
    std::list<int> &indices = pieceSquaresOfType[pieceType];
    indices.remove(oldRookPos);

    pieces[newRookPos] = pieceType;
    indices.push_back(newRookPos);
}

void Board::CheckCastleRights(int pieceType, int square)
{
    if (pieceType == (KING | playerToMove))
    {
        printf("King moved\n");
        RemoveKingsideCastle(playerToMove);
        RemoveQueensideCastle(playerToMove);
    }
    if (pieceType == (ROOK | playerToMove))
    {
        printf("Rook moved\n");
        if (FileIndex(square) == 0)
        {
            RemoveQueensideCastle(playerToMove);
        }
        else if (FileIndex(square) == 7)
        {
            RemoveKingsideCastle(playerToMove);
        }
    }
}

void Board::Promote(int promotionType, int square)
{
    pieces[square] = promotionType | playerToMove;
    std::list<int> &pawnIndices = pieceSquaresOfType[PAWN | playerToMove];
    std::list<int> &promotionIndices = pieceSquaresOfType[promotionType | playerToMove];
    pawnIndices.remove(square);
    promotionIndices.push_back(square);
}

void Board::FinishTurn()
{
    if (playerToMove == WHITE)
        playerToMove = BLACK;
    else
        playerToMove = WHITE;
}

bool Board::IsOutOfBounds(int x, int y)
{
    if (x < BOARD_X || x > BOARD_X + TILE_SIZE * ROW_SIZE || y < BOARD_Y || y > BOARD_Y + TILE_SIZE * COLUMN_SIZE)
    {
        return true;
    }
    return false;
}

int Board::GetHeldPiece()
{
    return heldPiece;
}

int Board::GetPlayerToMove()
{
    return playerToMove;
}

int Board::GetHeldPieceIndex()
{
    return heldPieceIndex;
}

int Board::GetPawnTwoSquareFile()
{
    return pawnTwoSquareFile;
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
