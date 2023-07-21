#include "headers/game.hpp"

void Game::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    running = true;
    playerToMove = &whitePlayer;

    while (running)
    {
        Update();
    }
}

void Game::Update()
{
    Move chosenMove = playerToMove->GetChosenMove();
    if (chosenMove.moveValue != 0)
        SwitchTurn(chosenMove);
    eventManager.Update(running, board, *playerToMove);
    renderer.Update(playerToMove->board, playerToMove->heldPiece, playerToMove->heldPieceIndex, playerToMove->colorToMove, playerToMove->board.pawnTwoSquareFile);
}

void Game::SwitchTurn(Move move)
{
    if (playerToMove == &whitePlayer)
        playerToMove = &blackPlayer;
    else
        playerToMove = &whitePlayer;
    playerToMove->NotifyTurnToMove(move);
}

void Game::Quit()
{
    renderer.Destroy();
    running = false;
}