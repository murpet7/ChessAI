#include "headers/board.hpp"
#include "board.hpp"
#include "matchInfo.hpp"

Board::Board(SDL_Renderer *renderer)
{
    SDL_Texture *wPawn = IMG_LoadTexture(renderer, "resources/gfx/pieces/w_pawn.png");
    SDL_Texture *wKnight = IMG_LoadTexture(renderer, "resources/gfx/pieces/w_knight.png");
    SDL_Texture *wBishop = IMG_LoadTexture(renderer, "resources/gfx/pieces/w_bishop.png");
    SDL_Texture *wRook = IMG_LoadTexture(renderer, "resources/gfx/pieces/w_rook.png");
    SDL_Texture *wQueen = IMG_LoadTexture(renderer, "resources/gfx/pieces/w_queen.png");
    SDL_Texture *wKing = IMG_LoadTexture(renderer, "resources/gfx/pieces/w_king.png");
    SDL_Texture *bPawn = IMG_LoadTexture(renderer, "resources/gfx/pieces/b_pawn.png");
    SDL_Texture *bKnight = IMG_LoadTexture(renderer, "resources/gfx/pieces/b_knight.png");
    SDL_Texture *bBishop = IMG_LoadTexture(renderer, "resources/gfx/pieces/b_bishop.png");
    SDL_Texture *bRook = IMG_LoadTexture(renderer, "resources/gfx/pieces/b_rook.png");
    SDL_Texture *bQueen = IMG_LoadTexture(renderer, "resources/gfx/pieces/b_queen.png");
    SDL_Texture *bKing = IMG_LoadTexture(renderer, "resources/gfx/pieces/b_king.png");

    pieceTextures[White | Pawn] = wPawn;
    pieceTextures[White | Knight] = wKnight;
    pieceTextures[White | Bishop] = wBishop;
    pieceTextures[White | Rook] = wRook;
    pieceTextures[White | Queen] = wQueen;
    pieceTextures[White | King] = wKing;
    pieceTextures[Black | Pawn] = bPawn;
    pieceTextures[Black | Knight] = bKnight;
    pieceTextures[Black | Bishop] = bBishop;
    pieceTextures[Black | Rook] = bRook;
    pieceTextures[Black | Queen] = bQueen;
    pieceTextures[Black | King] = bKing;

    PiecesFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

void Board::Draw(SDL_Renderer *renderer)
{
    DrawBoard(renderer);
    DrawPieces(renderer);
    DragPiece(renderer);
}

void Board::DrawBoard(SDL_Renderer *renderer)
{
    const SDL_Color lightColor = {0x42, 0x29, 0x1A, 0xFF};
    const SDL_Color darkColor = {0xDE, 0xB8, 0x86, 0xFF};
    SDL_Rect rect = {0, 0, tileSize, tileSize};
    SDL_Color color = {0, 0, 0, 255};
    for (int y = 0; y < rowSize; y++)
    {
        for (int x = 0; x < columnSize; x++)
        {
            if ((x + y) % 2 == 0)
            {
                color = darkColor;
            }
            else
            {
                color = lightColor;
            }
            rect.x = x * tileSize;
            rect.y = y * tileSize;
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void Board::DrawPieces(SDL_Renderer *renderer)
{
    for (int y = 0; y < rowSize; y++)
    {
        for (int x = 0; x < columnSize; x++)
        {
            SDL_Rect rect = {x * tileSize + boardX, y * tileSize + boardY, tileSize, tileSize};
            SDL_Texture *texture = pieceTextures[pieces[x][y]];
            SDL_RenderCopy(renderer, texture, NULL, &rect);
        }
    }
}

int *Board::GetTileFromMouse(int mouseX, int mouseY)
{
    int tileX = (mouseX - boardX) / tileSize;
    int tileY = (mouseY - boardY) / tileSize;
    int *tile = new int[2];
    tile[0] = tileX;
    tile[1] = tileY;
    return tile;
}

void Board::PickupPiece(int x, int y)
{
    int *tile = GetTileFromMouse(x, y);
    int tileX = tile[0];
    int tileY = tile[1];
    int piece = pieces[tileX][tileY];
    if (GetPieceColor(piece) != curPlayerColor)
        return;
    if (piece != None)
    {
        curPiece = piece;
        pieces[tileX][tileY] = None;
    }
    prevX = tileX;
    prevY = tileY;
}

void Board::DropPiece(int x, int y)
{
    if (curPiece == -1)
        return;
    if (IsOutOfBounds(x, y))
    {
        pieces[prevX][prevY] = curPiece;
        curPiece = -1;
        return;
    }
    int *tile = GetTileFromMouse(x, y);
    int tileX = tile[0];
    int tileY = tile[1];
    if (pieces[tileX][tileY] == None || IsOpposingColor(curPiece, pieces[tileX][tileY]))
    {
        pieces[tileX][tileY] = curPiece;
        curPiece = -1;
        ChangePlayerColor();
    }
    else
    {
        pieces[prevX][prevY] = curPiece;
        curPiece = -1;
    }
}

void Board::ChangePlayerColor()
{
    if (curPlayerColor == White)
        curPlayerColor = Black;
    else
        curPlayerColor = White;
}

bool Board::IsOutOfBounds(int x, int y)
{
    if (x < boardX || x > boardX + tileSize * rowSize || y < boardY || y > boardY + tileSize * columnSize)
    {
        return true;
    }
    return false;
}

bool Board::IsOpposingColor(int piece1, int piece2)
{
    if (GetPieceColor(piece1) != GetPieceColor(piece2))
        return true;
    return false;
}

int Board::GetPieceColor(int piece)
{
    if (piece == None)
        return None;
    if (piece & White)
        return White;
    return Black;
}

void Board::DragPiece(SDL_Renderer *renderer)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (curPiece != -1)
    {
        SDL_Rect rect = {mouseX - tileSize / 2, mouseY - tileSize / 2, tileSize, tileSize};
        SDL_Texture *texture = pieceTextures[curPiece];
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
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
                pieces[x][y] = Black | Pawn;
                break;
            case 'n':
                pieces[x][y] = Black | Knight;
                break;
            case 'b':
                pieces[x][y] = Black | Bishop;
                break;
            case 'r':
                pieces[x][y] = Black | Rook;
                break;
            case 'q':
                pieces[x][y] = Black | Queen;
                break;
            case 'k':
                pieces[x][y] = Black | King;
                break;
            case 'P':
                pieces[x][y] = White | Pawn;
                break;
            case 'N':
                pieces[x][y] = White | Knight;
                break;
            case 'B':
                pieces[x][y] = White | Bishop;
                break;
            case 'R':
                pieces[x][y] = White | Rook;
                break;
            case 'Q':
                pieces[x][y] = White | Queen;
                break;
            case 'K':
                pieces[x][y] = White | King;
                break;
            }
            x++;
        }
    }
}