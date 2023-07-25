#pragma once

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "headers/move.hpp"
#include "headers/piece.hpp"
#include "headers/boardRepresentation.hpp"

#define BOARD_X 0
#define BOARD_Y 0
#define TILE_SIZE 80
#define ROW_SIZE 8
#define COLUMN_SIZE 8

#define WHITE_CASTLE_KINGSIDE_MASK 0b0001
#define WHITE_CASTLE_QUEENSIDE_MASK 0b0010
#define BLACK_CASTLE_KINGSIDE_MASK 0b0100
#define BLACK_CASTLE_QUEENSIDE_MASK 0b1000

class Board
{
public:
    int pieces[64] = {NONE};

    unsigned short castleMask = 0b1111;
    int pawnTwoSquareFile = -2;
    int colorToMove = WHITE;
    std::map<int, SDL_Texture *> pieceTextures;
    std::map<int, std::vector<int>> pieceSquaresOfType;
    Board();
    void PiecesFromFEN(std::string FEN);

    // void PickupPiece(int x, int y);
    // void DropPiece(int x, int y);
    // int GetHeldPiece();
    // int GetHeldPieceIndex();
    // int GetPlayerToMove();
    // int GetPawnTwoSquareFile();
    void MakeMove(Move move);

    static bool CanCastleKingside(int colorToMove, int castleMask);
    static bool CanCastleQueenside(int colorToMove, int castleMask);
    void RemoveKingsideCastle(int colorToMove);
    void RemoveQueensideCastle(int colorToMove);

    int GetKingSquare(int color);

private:
    // bool IsOutOfBounds(int x, int y);
    // void ReturnHeldPiece();
    void Castle(int oldRookPos, int newRookPos);
    void CheckCastleRights(int pieceType, int square);
    void FinishTurn();
    void Promote(int promotionType, int square);
    int PieceTypeFromChar(char c);
    // int GetTileFromMouse(int mouseX, int mouseY);
};