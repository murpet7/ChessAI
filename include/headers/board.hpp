#pragma once

#include <string>
#include <map>
#include <list>
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

class Board
{
public:
    int pieces[64] = {NONE};

    unsigned short castleMask = 0b1111;
    int pawnTwoSquareFile = -2;
    int colorToMove = WHITE;
    std::map<int, SDL_Texture *> pieceTextures;
    std::map<int, std::list<int>> pieceSquaresOfType;
    Board();
    void PiecesFromFEN(std::string FEN);

    // void PickupPiece(int x, int y);
    // void DropPiece(int x, int y);
    // int GetHeldPiece();
    // int GetHeldPieceIndex();
    // int GetPlayerToMove();
    // int GetPawnTwoSquareFile();
    void MovePiece(Move move);

    const unsigned short whiteCastleKingsideMask = 0b0001;
    const unsigned short whiteCastleQueensideMask = 0b0010;
    const unsigned short blackCastleKingsideMask = 0b0100;
    const unsigned short blackCastleQueensideMask = 0b1000;

    bool CanCastleKingside(int colorToMove);
    bool CanCastleQueenside(int colorToMove);
    void RemoveKingsideCastle(int colorToMove);
    void RemoveQueensideCastle(int colorToMove);

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