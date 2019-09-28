#ifndef HUMANOID_H
#define HUMANOID_H

typedef struct
{
    int x, y, w, h;
    int dy;
    int dx;
    float life;
    float max_life;
    char* name;
    int facingLeft;
} Humanoid;

void show_life(Humanoid* humanoid, SDL_Renderer* renderer)
{
    // Create a rectangle
    SDL_Rect r;
    r.x = humanoid->x;
    r.w = 50;
    r.h = 3;
    r.y = humanoid->y - 2 * r.h;
    SDL_Rect r2;
    r2.x = humanoid->x;
    r2.w = humanoid->life / humanoid->max_life * 50;
    r2.h = 3;
    r2.y = humanoid->y - 2 * r.h;
    // Change color to blue!
    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
    SDL_RenderFillRect(renderer, &r);
    SDL_RenderDrawRect(renderer, &r);
    // Change color to red!
    SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
    SDL_RenderFillRect(renderer, &r2);
    SDL_RenderDrawRect(renderer, &r2);
}

#endif