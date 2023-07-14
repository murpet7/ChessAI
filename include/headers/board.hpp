#pragma once

#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "headers/piece.hpp"

#define boardX 0
#define boardY 0
#define tileSize 80
#define rowSize 8
#define columnSize 8

class Board
{
public:
    Board() = default;
    Board(SDL_Renderer *renderer);
    int pieces[8][8] = {None};
    void Draw(SDL_Renderer *renderer);
    void DrawBoard(SDL_Renderer *renderer);
    void DrawPieces(SDL_Renderer *renderer);
    void PiecesFromFEN(std::string FEN);
    int *GetTileFromMouse(int mouseX, int mouseY);
    void PickupPiece(int x, int y);
    void DropPiece(int x, int y);
    void DragPiece(SDL_Renderer *renderer);

private:
    std::map<int, SDL_Texture *> pieceTextures;
    int curPiece = -1;
    int prevX;
    int prevY;
    bool IsOutOfBounds(int x, int y);
    bool IsOpposingColor(int piece1, int piece2);
    int GetPieceColor(int piece);
    void ChangePlayerColor();
};