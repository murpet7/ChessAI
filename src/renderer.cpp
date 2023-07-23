#include "headers/renderer.hpp"

Renderer::Renderer()
{
    this->pieceTextures = pieceTextures;
    SDL_Window *window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    SDLRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!SDLRenderer)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    LoadPieceTextures();
}

void Renderer::LoadPieceTextures()
{
    SDL_Texture *wPawn = IMG_LoadTexture(SDLRenderer, "resources/gfx/pieces/w_pawn.png");
    SDL_Texture *wKnight = IMG_LoadTexture(SDLRenderer, "resources/gfx/pieces/w_knight.png");
    SDL_Texture *wBishop = IMG_LoadTexture(SDLRenderer, "resources/gfx/pieces/w_bishop.png");
    SDL_Texture *wRook = IMG_LoadTexture(SDLRenderer, "resources/gfx/pieces/w_rook.png");
    SDL_Texture *wQueen = IMG_LoadTexture(SDLRenderer, "resources/gfx/pieces/w_queen.png");
    SDL_Texture *wKing = IMG_LoadTexture(SDLRenderer, "resources/gfx/pieces/w_king.png");
    SDL_Texture *bPawn = IMG_LoadTexture(SDLRenderer, "resources/gfx/pieces/b_pawn.png");
    SDL_Texture *bKnight = IMG_LoadTexture(SDLRenderer, "resources/gfx/pieces/b_knight.png");
    SDL_Texture *bBishop = IMG_LoadTexture(SDLRenderer, "resources/gfx/pieces/b_bishop.png");
    SDL_Texture *bRook = IMG_LoadTexture(SDLRenderer, "resources/gfx/pieces/b_rook.png");
    SDL_Texture *bQueen = IMG_LoadTexture(SDLRenderer, "resources/gfx/pieces/b_queen.png");
    SDL_Texture *bKing = IMG_LoadTexture(SDLRenderer, "resources/gfx/pieces/b_king.png");

    pieceTextures[WHITE | PAWN] = wPawn;
    pieceTextures[WHITE | KNIGHT] = wKnight;
    pieceTextures[WHITE | BISHOP] = wBishop;
    pieceTextures[WHITE | ROOK] = wRook;
    pieceTextures[WHITE | QUEEN] = wQueen;
    pieceTextures[WHITE | KING] = wKing;
    pieceTextures[BLACK | PAWN] = bPawn;
    pieceTextures[BLACK | KNIGHT] = bKnight;
    pieceTextures[BLACK | BISHOP] = bBishop;
    pieceTextures[BLACK | ROOK] = bRook;
    pieceTextures[BLACK | QUEEN] = bQueen;
    pieceTextures[BLACK | KING] = bKing;
}

void Renderer::Update(Board board, int heldPiece, int heldPieceSquare, int colorToMove, int pawnTwoSquareFile)
{
    RenderBackground();
    RenderBoard();
    RenderLegalMoves(board, heldPiece, heldPieceSquare, colorToMove, pawnTwoSquareFile);
    RenderPieces(board, heldPieceSquare, heldPiece);
    RenderDraggedPiece(heldPiece);
    SDL_RenderPresent(SDLRenderer);
}

void Renderer::RenderBoard()
{
    const SDL_Color lightColor = {0x42, 0x29, 0x1A, 0xFF};
    const SDL_Color darkColor = {0xDE, 0xB8, 0x86, 0xFF};
    SDL_Rect rect = {0, 0, TILE_SIZE, TILE_SIZE};
    SDL_Color color = {0, 0, 0, 255};
    for (int y = 0; y < ROW_SIZE; y++)
    {
        for (int x = 0; x < COLUMN_SIZE; x++)
        {
            if ((x + y) % 2 == 0)
            {
                color = darkColor;
            }
            else
            {
                color = lightColor;
            }
            rect.x = x * TILE_SIZE;
            rect.y = y * TILE_SIZE;
            SDL_SetRenderDrawColor(SDLRenderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(SDLRenderer, &rect);
        }
    }
}

void Renderer::RenderPieces(Board board, int heldPieceSquare, int heldPiece)
{
    for (int y = 0; y < ROW_SIZE; y++)
    {
        for (int x = 0; x < COLUMN_SIZE; x++)
        {
            if (Square(x, y) == heldPieceSquare && heldPiece != NONE)
                continue;
            SDL_Rect rect = {x * TILE_SIZE + BOARD_X, y * TILE_SIZE + BOARD_Y, TILE_SIZE, TILE_SIZE};
            SDL_Texture *texture = pieceTextures[board.pieces[Square(x, y)]];
            SDL_RenderCopy(SDLRenderer, texture, NULL, &rect);
        }
    }
}

void Renderer::RenderDraggedPiece(int heldPiece)
{
    if (heldPiece == NONE)
        return;
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect rect = {mouseX - TILE_SIZE / 2, mouseY - TILE_SIZE / 2, TILE_SIZE, TILE_SIZE};
    SDL_Texture *texture = pieceTextures[heldPiece];
    SDL_RenderCopy(SDLRenderer, texture, NULL, &rect);
}

void Renderer::RenderLegalMoves(Board board, int heldPiece, int heldPieceSquare, int colorToMove, int pawnTwoSquareFile)
{
    if (heldPiece == NONE)
        return;
    std::vector<Move> legalMoves = MoveGenerator::GenerateMovesForPiece(board, heldPieceSquare, heldPiece);
    for (Move move : legalMoves)
    {
        SDL_Rect rect = {File(move.GetTo()) * TILE_SIZE + BOARD_X, Rank(move.GetTo()) * TILE_SIZE + BOARD_Y, TILE_SIZE, TILE_SIZE};
        SDL_SetRenderDrawColor(SDLRenderer, 0, 255, 0, 255);
        SDL_RenderFillRect(SDLRenderer, &rect);
    }
}

void Renderer::RenderBackground()
{
    SDL_SetRenderDrawColor(SDLRenderer, 170, 170, 170, 255);
    SDL_RenderClear(SDLRenderer);
}

void Renderer::Destroy()
{
    SDL_DestroyRenderer(SDLRenderer);
    SDL_DestroyWindow(window);
}