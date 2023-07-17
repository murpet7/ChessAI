#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

#include "headers/board.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Renderer
{
public:
    SDL_Window *window;
    SDL_Renderer *SDLRenderer;

    Renderer();
    void Update(Board board, int heldPiece);
    void Destroy();

private:
    std::map<int, SDL_Texture *> pieceTextures;
    void LoadPieceTextures();
    void RenderBoard();
    void RenderPieces(Board board);
    void RenderDraggedPiece(int heldPiece);
    void RenderBackground();
};