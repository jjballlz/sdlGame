#ifndef HUMANOID_H
#define HUMANOID_H

void show_life(Humanoid* humanoid, SDL_Renderer* renderer)
{
    // Create a rectangle
    SDL_Rect r;
    r.x = humanoid->x;
    r.y = humanoid->y - humanoid->h - 10;
    r.w = 50;
    r.h = 5;

    // Change color to blue!
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &r);
    // The rectangle will now be blue
    SDL_RenderDrawRect(renderer, &r);
}
#endif