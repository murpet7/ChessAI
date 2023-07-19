#include "headers/moveManager.hpp"

int MoveManager::GetTileFromMouse(int mouseX, int mouseY)
{
    if (IsOutOfBounds(mouseX, mouseY))
        return -1;
    int tileX = (mouseX - BOARD_X) / TILE_SIZE;
    int tileY = (mouseY - BOARD_Y) / TILE_SIZE;
    return SquareIndex(tileX, tileY);
}

void MoveManager::PickupPiece(int x, int y, Board &board)
{
    heldPieceIndex = GetTileFromMouse(x, y);
    heldPiece = board.pieces[heldPieceIndex];
    board.pieces[heldPieceIndex] = NONE;
    std::list<int> &indices = board.pieceSquaresOfType[heldPiece];
    indices.remove(heldPieceIndex);
    if (PieceIsColor(heldPiece, playerToMove) || heldPiece == NONE)
        ReturnHeldPiece(board);
}

void MoveManager::DropPiece(int x, int y, Board &board)
{
    if (heldPiece == NONE)
        return;
    int newSquare = GetTileFromMouse(x, y);
    Move move = MoveFromStartAndEnd(heldPieceIndex, newSquare, playerToMove, board.pieces, heldPiece, pawnTwoSquareFile, board);
    if (newSquare != -1 && move.moveValue != 0)
    {
        MoveHeldPiece(move, board);
        FinishTurn();
    }
    else
    {
        ReturnHeldPiece(board);
    }
}

void MoveManager::ReturnHeldPiece(Board &board)
{
    board.pieces[heldPieceIndex] = heldPiece;
    std::list<int> &indices = board.pieceSquaresOfType[heldPiece];
    indices.push_back(heldPieceIndex);
    heldPiece = NONE;
}

void MoveManager::MoveHeldPiece(Move move, Board &board)
{
    int to = move.GetTo();
    int from = move.GetFrom();

    CheckCastleRights(heldPiece, from, board);

    board.pieces[to] = heldPiece;
    std::list<int> &indices = board.pieceSquaresOfType[heldPiece];
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
        board.pieces[captureSquare] = NONE;
    }

    if (flag == CASTLE)
    {
        if (FileIndex(to) == 2)
        {
            Castle(to - 2, to + 1, board);
        }
        else
        {
            Castle(to + 1, to - 1, board);
        }
    }

    if (flag == QUEEN_PROMOTION)
    {
        Promote(QUEEN, to, board);
    }
    else if (flag == ROOK_PROMOTION)
    {
        Promote(ROOK, to, board);
    }
    else if (flag == BISHOP_PROMOTION)
    {
        Promote(BISHOP, to, board);
    }
    else if (flag == KNIGHT_PROMOTION)
    {
        Promote(KNIGHT, to, board);
    }
}

void MoveManager::Castle(int oldRookPos, int newRookPos, Board &board)
{
    int pieceType = ROOK | playerToMove;

    board.pieces[oldRookPos] = NONE;
    std::list<int> &indices = board.pieceSquaresOfType[pieceType];
    indices.remove(oldRookPos);

    board.pieces[newRookPos] = pieceType;
    indices.push_back(newRookPos);
}

void MoveManager::CheckCastleRights(int pieceType, int square, Board &board)
{
    if (pieceType == (KING | playerToMove))
    {
        printf("King moved\n");
        board.RemoveKingsideCastle(playerToMove);
        board.RemoveQueensideCastle(playerToMove);
    }
    if (pieceType == (ROOK | playerToMove))
    {
        printf("Rook moved\n");
        if (FileIndex(square) == 0)
        {
            board.RemoveQueensideCastle(playerToMove);
        }
        else if (FileIndex(square) == 7)
        {
            board.RemoveKingsideCastle(playerToMove);
        }
    }
}

void MoveManager::Promote(int promotionType, int square, Board &board)
{
    board.pieces[square] = promotionType | playerToMove;
    std::list<int> &pawnIndices = board.pieceSquaresOfType[PAWN | playerToMove];
    std::list<int> &promotionIndices = board.pieceSquaresOfType[promotionType | playerToMove];
    pawnIndices.remove(square);
    promotionIndices.push_back(square);
}

void MoveManager::FinishTurn()
{
    if (playerToMove == WHITE)
        playerToMove = BLACK;
    else
        playerToMove = WHITE;
}

bool MoveManager::IsOutOfBounds(int x, int y)
{
    if (x < BOARD_X || x > BOARD_X + TILE_SIZE * ROW_SIZE || y < BOARD_Y || y > BOARD_Y + TILE_SIZE * COLUMN_SIZE)
    {
        return true;
    }
    return false;
}

int MoveManager::GetHeldPiece()
{
    return heldPiece;
}

int MoveManager::GetPlayerToMove()
{
    return playerToMove;
}

int MoveManager::GetHeldPieceIndex()
{
    return heldPieceIndex;
}

int MoveManager::GetPawnTwoSquareFile()
{
    return pawnTwoSquareFile;
}