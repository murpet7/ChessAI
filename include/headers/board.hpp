#pragma once

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <stack>
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

#define EN_PASSANT_FILE_MASK 0b0000011110000
#define CAPTURED_PIECE_MASK 0b1111100000000
#define STARTING_GAME_STATE 0b000000001111

#define STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"

class Board
{
public:
    Board();
    Board(std::string FEN);

    void MakeMove(Move &move);
    void UndoMove(Move &move);

    void AddPiece(int pieceType, int square);
    void RemovePiece(int pieceType, int square);

    int *GetPieces();
    int GetColorToMove();
    std::vector<int> GetPieceSquares(int piece);

    int GetKingSquare(int kingColor);
    int GetCapturedPiece();
    int GetEnPassantFile();

    bool CanCastleKingside();
    bool CanCastleQueenside();

private:
    int colorToMove = WHITE;
    int pieces[64] = {NONE};
    std::stack<unsigned short> gameStateHistory;

    std::map<int, SDL_Texture *> pieceTextures;
    std::map<int, std::vector<int>> pieceSquaresTable;

    void Castle(int to);
    void UndoCastle(int to);
    void Promote(int promotionType, int square);
    void MovePiece(int pieceType, int from, int to);
    void UpdateEnPassantFile(unsigned short &gameState, int file);
    void UpdateCapturedPiece(unsigned short &gameState, int piece);
    void ChangeColorToMove();

    void RemoveCastleRights(unsigned short &gameState, int piece, int square);
    void RemoveKingsideCastle(unsigned short &gameState);
    void RemoveQueensideCastle(unsigned short &gameState);
};