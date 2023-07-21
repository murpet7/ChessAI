#include "headers/eventManager.hpp"

void EventManager::Update(bool &running, Player &playerToMove)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            OnMouseDown(playerToMove);
            break;
        case SDL_MOUSEBUTTONUP:
            OnMouseUp(playerToMove);
            break;
        }
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                running = false;
                break;
            }
        }
    }
}

void EventManager::OnMouseDown(Player &playerToMove)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    playerToMove.PickupPiece(mouseX, mouseY);
}

void EventManager::OnMouseUp(Player &playerToMove)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    playerToMove.DropPiece(mouseX, mouseY);
}