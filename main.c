
#include <time.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "main.h"
#include "event.h"
#include "physics.h"
#include "image.h"
#include "humanoid.h"

void GameInit(GameState* game)
{
    // set the man to coo and correct size
    game->man.x = 540;
    game->man.y = 30;
    game->man.w = 60;
    game->man.h = 60;
    game->man.dy = 0;
    game->man.dx = 0;
    game->man.facingLeft = 0;
    game->man.life = 80;
    game->man.max_life = 100;
    // set the man to coo and correct size
    game->monstre1.x = 500;
    game->monstre1.y = 300;
    game->monstre1.w = 60;
    game->monstre1.h = 60;
    game->monstre1.dy = 0;
    game->monstre1.dx = 0;
    game->monstre1.facingLeft = 0;
    // set where the screen start (now the man is in left corner)
    game->scrollX = 0;
    game->scrollY = 0;
    game->rightScreen = 180;
    game->leftScreen = 80;
    game->bottomScreen = 720;
    game->topScreen = 80;
    //init star
    for (int i = 0; i < sizeof(game->star) / sizeof(game->star[0]); i++) {
        game->star[i].x = -30000;
        game->star[i].y = -30000;
        game->star[i].w = 30;
        game->star[i].h = 30;
    }
    game->nbr_star = 0;
    // init all the ledges
    for (int i = 0; i < sizeof(game->ledges) / sizeof(game->ledges[0]); ++i) {
        game->ledges[i].w = 50;
        game->ledges[i].h = 50;
        game->ledges[i].x = i * game->ledges[i].w;
        game->ledges[i].y = 670;
    }
    for (int i = 90; i < sizeof(game->ledges) / sizeof(game->ledges[0]); i++) {
        game->ledges[i].x = 500 + (i - 90) * game->ledges[i].w;
        game->ledges[i].y = 450;
    }
    for (int i = 80; i < 90; i++) {
        game->ledges[i].x = 100 + (i - 80) * game->ledges[i].w;
        game->ledges[i].y = 620;
    }
    init_image(game);
}

void doRender(GameState* game)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
    SDL_RenderClear(game->renderer);

    SDL_Rect bgRect = {0, 0, 1080, 720};
    SDL_RenderCopy(game->renderer, game->bgTexture, NULL, &bgRect);

    for (int i = 0; i < sizeof(game->ledges) / sizeof(game->ledges[0]); ++i) {
        SDL_Rect ledgeRect = {game->ledges[i].x, game->ledges[i].y, game->ledges[i].w, game->ledges[i].h};
        SDL_RenderCopy(game->renderer, game->ledgeTexture, NULL, &ledgeRect);
    }

    show_life(&game->man, game->renderer);
    show_life(&game->monstre1, game->renderer);
    SDL_Rect manRect = {game->man.x, game->man.y, game->man.w, game->man.h};
    SDL_RenderCopyEx(game->renderer, game->manTexture, NULL, &manRect, 0, NULL, (game->man.facingLeft == 1));

    SDL_Rect monstre1Rect = {game->monstre1.x, game->monstre1.y, game->monstre1.w, game->monstre1.h};
    SDL_RenderCopyEx(game->renderer, game->monstre1Texture, NULL, &monstre1Rect, 0, NULL, (game->monstre1.facingLeft == 1));

    for (int i = 0; i < sizeof(game->star) / sizeof(game->star[0]); i++) {
        game->star[i].x += game->star[i].dx;
        SDL_Rect starRect = {game->star[i].x, game->star[i].y, game->star[i].w, game->star[i].h};
        SDL_RenderCopyEx(game->renderer, game->starTexture, NULL, &starRect, 0, NULL, 0);
    }
    SDL_RenderPresent(game->renderer);
}

int main(int argc, char* argv[])
{
    int done = 0;
    srandom((int)time(NULL));

    GameState gameState;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Game Window",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              1080,
                              720,
                              0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    gameState.renderer = renderer;

    GameInit(&gameState);

    while (!done) {
        if (processEvent(window, &gameState) == 1) {
            done = 1;
        }

        processGravity(&gameState.man);
        processGravity(&gameState.monstre1);
        collisionDetection(&gameState);
        collisionDetectionMonster(&gameState);
        scrolling(&gameState);
        doRender(&gameState);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
    return 0;
}
