#include "headers/eventManager.hpp"

void EventManager::Update(bool &running, MoveManager &moveManager, Board &board)
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
            OnMouseDown(moveManager, board);
            break;
        case SDL_MOUSEBUTTONUP:
            OnMouseUp(moveManager, board);
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

void EventManager::OnMouseDown(MoveManager &moveManager, Board &board)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    moveManager.PickupPiece(mouseX, mouseY, board);
}

void EventManager::OnMouseUp(MoveManager &moveManager, Board &board)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    moveManager.DropPiece(mouseX, mouseY, board);
}