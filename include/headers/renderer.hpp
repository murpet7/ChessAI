#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <vector>

#include "headers/board.hpp"
#include "headers/moveGenerator.hpp"
#include "headers/boardRepresentation.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Renderer
{
public:
    SDL_Window *window;
    SDL_Renderer *SDLRenderer;

    Renderer();
    void Update(Board board, int heldPiece, int heldPieceSquare, int colorToMove, int enPassantFile);
    void Destroy();

private:
    std::map<int, SDL_Texture *> pieceTextures;
    void LoadPieceTextures();
    void RenderBoard();
    void RenderPieces(Board board, int heldPieceSquare, int heldPiece);
    void RenderDraggedPiece(int heldPiece);
    void RenderBackground();
    void RenderLegalMoves(Board board, int heldPiece, int heldPieceSquare, int colorToMove, int enPassantFile);
};