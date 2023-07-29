#include "headers/board.hpp"
#include "headers/moveGenerator.hpp"
#include "headers/FENManager.hpp"

Board::Board()
{
    FENManager::PiecesFromFEN(*this, STARTING_FEN);
    gameStateHistory.push(STARTING_GAME_STATE);
}

Board::Board(std::string FEN)
{
    FENManager::PiecesFromFEN(*this, FEN);
    gameStateHistory.push(STARTING_GAME_STATE);
}

void Board::MakeMove(Move &move)
{
    int to = move.GetTo();
    int from = move.GetFrom();
    int pieceType = pieces[from];
    unsigned short gameState = gameStateHistory.top();

    UpdateCapturedPiece(gameState, NONE);
    UpdateEnPassantFile(gameState, 15); // 15 is an invalid file

    RemoveCastleRights(gameState, pieceType, from);

    int capturedPieceType = pieces[to];
    if (capturedPieceType != NONE)
    {
        RemovePiece(capturedPieceType, to);
        UpdateCapturedPiece(gameState, capturedPieceType);
    }
    MovePiece(pieceType, from, to);

    int flag = move.GetFlag();
    switch (flag)
    {
    case PAWN_TWO_SQUARES:
        UpdateEnPassantFile(gameState, File(to));
        break;
    case EN_PASSANT:
        RemovePiece(capturedPieceType, Square(File(to), Rank(from)));
        break;
    case CASTLE:
        Castle(to);
        break;
    case QUEEN_PROMOTION:
        Promote(QUEEN, to);
        break;
    case ROOK_PROMOTION:
        Promote(ROOK, to);
        break;
    case BISHOP_PROMOTION:
        Promote(BISHOP, to);
        break;
    case KNIGHT_PROMOTION:
        Promote(KNIGHT, to);
        break;
    }
    gameStateHistory.push(gameState);
    ChangeColorToMove();
}

void Board::UndoMove(Move &move)
{
    int to = move.GetTo();
    int from = move.GetFrom();
    int pieceType = pieces[to];

    int capturedPieceType = GetCapturedPiece();
    MovePiece(pieceType, to, from);
    if (capturedPieceType != NONE)
    {
        AddPiece(capturedPieceType, to);
    }

    int flag = move.GetFlag();
    switch (flag)
    {
    case PAWN_TWO_SQUARES:
        break;
    case EN_PASSANT:
        AddPiece(PAWN, Square(File(to), Rank(from)));
        break;
    case CASTLE:
        UndoCastle(to);
        break;
    case QUEEN_PROMOTION:
        RemovePiece(QUEEN | colorToMove, to);
        AddPiece(PAWN | colorToMove, from);
        break;
    case ROOK_PROMOTION:
        RemovePiece(ROOK | colorToMove, to);
        AddPiece(PAWN | colorToMove, from);
        break;
    case BISHOP_PROMOTION:
        RemovePiece(BISHOP | colorToMove, to);
        AddPiece(PAWN | colorToMove, from);
        break;
    case KNIGHT_PROMOTION:
        RemovePiece(KNIGHT | colorToMove, to);
        AddPiece(PAWN | colorToMove, from);
        break;
    }
    gameStateHistory.pop();
    ChangeColorToMove();
}

void Board::MovePiece(int piece, int oldSquare, int newSquare)
{
    pieces[oldSquare] = NONE;
    pieces[newSquare] = piece;
    std::vector<int> &indices = pieceSquaresTable[piece];
    indices.erase(std::remove(indices.begin(), indices.end(), oldSquare), indices.end());
    indices.push_back(newSquare);
}

void Board::AddPiece(int piece, int square)
{
    pieces[square] = piece;
    std::vector<int> &indices = pieceSquaresTable[piece];
    indices.push_back(square);
}

void Board::RemovePiece(int piece, int square)
{
    pieces[square] = NONE;
    std::vector<int> &indices = pieceSquaresTable[piece];
    indices.erase(std::remove(indices.begin(), indices.end(), square), indices.end());
}

void Board::Castle(int to)
{
    int rank = Rank(to);
    if (File(to) == 6)
    {
        MovePiece(ROOK | colorToMove, Square(7, rank), Square(5, rank));
    }
    else
    {
        MovePiece(ROOK | colorToMove, Square(0, rank), Square(3, rank));
    }
}

void Board::UndoCastle(int to)
{
    int rank = Rank(to);
    if (File(to) == 6)
    {
        MovePiece(ROOK | OppositeColor(colorToMove), Square(5, rank), Square(7, rank));
    }
    else
    {
        MovePiece(ROOK | OppositeColor(colorToMove), Square(3, rank), Square(0, rank));
    }
}

void Board::RemoveCastleRights(unsigned short &gameState, int piece, int square)
{
    if (piece == (KING | colorToMove))
    {
        RemoveKingsideCastle(gameState);
        RemoveQueensideCastle(gameState);
    }
    if (piece == (ROOK | colorToMove))
    {
        if (File(square) == 0)
        {
            RemoveQueensideCastle(gameState);
        }
        else if (File(square) == 7)
        {
            RemoveKingsideCastle(gameState);
        }
    }
}

void Board::Promote(int promotionType, int square)
{
    pieces[square] = promotionType | colorToMove;
    std::vector<int> &pawnIndices = pieceSquaresTable[PAWN | colorToMove];
    std::vector<int> &promotionIndices = pieceSquaresTable[promotionType | colorToMove];
    pawnIndices.erase(std::remove(pawnIndices.begin(), pawnIndices.end(), square), pawnIndices.end());
    promotionIndices.push_back(square);
}

void Board::ChangeColorToMove()
{
    if (colorToMove == WHITE)
        colorToMove = BLACK;
    else
        colorToMove = WHITE;
}

void Board::UpdateEnPassantFile(unsigned short &gameState, int file)
{
    gameState &= ~EN_PASSANT_FILE_MASK;
    gameState |= file << 4;
}

int Board::GetEnPassantFile()
{
    return (gameStateHistory.top() & EN_PASSANT_FILE_MASK) >> 4;
}

void Board::UpdateCapturedPiece(unsigned short &gameState, int pieceType)
{
    gameState &= ~CAPTURED_PIECE_MASK;
    gameState |= pieceType << 8;
}

int Board::GetCapturedPiece()
{
    return (gameStateHistory.top() & CAPTURED_PIECE_MASK) >> 8;
}

int *Board::GetPieces()
{
    return pieces;
}

std::vector<int> Board::GetPieceSquares(int piece)
{
    return pieceSquaresTable[piece];
}

int Board::GetColorToMove()
{
    return colorToMove;
}

bool Board::CanCastleKingside()
{
    if (colorToMove == WHITE)
        return gameStateHistory.top() & WHITE_CASTLE_KINGSIDE_MASK;
    else
        return gameStateHistory.top() & BLACK_CASTLE_KINGSIDE_MASK;
}

bool Board::CanCastleQueenside()
{
    if (colorToMove == WHITE)
        return gameStateHistory.top() & WHITE_CASTLE_QUEENSIDE_MASK;
    else
        return gameStateHistory.top() & BLACK_CASTLE_QUEENSIDE_MASK;
}

void Board::RemoveKingsideCastle(unsigned short &gameState)
{
    if (colorToMove == WHITE)
        gameState &= ~WHITE_CASTLE_KINGSIDE_MASK;
    else
        gameState &= ~BLACK_CASTLE_KINGSIDE_MASK;
}

void Board::RemoveQueensideCastle(unsigned short &gameState)
{
    if (colorToMove == WHITE)
        gameState &= ~WHITE_CASTLE_QUEENSIDE_MASK;
    else
        gameState &= ~BLACK_CASTLE_QUEENSIDE_MASK;
}

int Board::GetKingSquare(int kingColor)
{
    std::vector<int> &pieceSquares = pieceSquaresTable[KING | kingColor];
    if (pieceSquares.size() == 0)
    {
        printf("No king found\n");
        return -1;
    }
    return pieceSquares.front();
}
