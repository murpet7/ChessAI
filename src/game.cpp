#include "headers/game.hpp"

// RUN: minGW32-make && ./main.exe
// DEBUG: CFLAGS='-g -Wall -Wextra' minGW32-make && gdb ./main.exe -ex run

void Game::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    running = true;
    playerToMove = &whitePlayer;
    playerToMove->NotifyTurnToMove(Move());

    while (running)
    {
        Update();
    }
}

void Game::Update()
{
    Move chosenMove = playerToMove->GetChosenMove();
    if (chosenMove.moveValue != 0)
    {
        SwitchTurn(chosenMove);
    }

    eventManager.Update(running, *playerToMove);
    renderer.Update(whitePlayer.board, playerToMove->heldPiece, playerToMove->heldPieceIndex, whitePlayer.board.GetColorToMove(), whitePlayer.board.GetEnPassantFile());
}

void Game::SwitchTurn(Move move)
{
    for (int square : playerToMove->board.GetPieceSquares(PAWN | BLACK))
    {
        printf("rank, %d ", Rank(square));
    }
    board.MakeMove(move);
    if (playerToMove == &whitePlayer)
        playerToMove = &blackPlayer;
    else
    {
        playerToMove = &whitePlayer;
    }

    playerToMove->NotifyTurnToMove(move);
}

void Game::Quit()
{
    renderer.Destroy();
    running = false;
}