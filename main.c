
#include <time.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "main.h"

#define GRAVITY 0.8f

int processEvent(SDL_Window* window, GameState* game)
{
    SDL_Event event;
    int done = 0;

    while (SDL_PollEvent(&event)) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                done = 1;
                break;
                //case SDLK_UP:
                //	if(game->man.dy == 0.0f)
                //	{
                //	game->man.dy = -15;
                //	}
                //break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        done = 1;
    }
    if (state[SDL_SCANCODE_LEFT]) {
        game->man.dx -= 0.6f;
        game->man.facingLeft = 1;
        if (game->man.dx <= -6.5f) {
            game->man.dx = -6.5f;
        }
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        game->man.dx += 0.6f;
        game->man.facingLeft = 0;
        if (game->man.dx >= 6.5f) {
            game->man.dx = 6.5f;
        }
    }

    if (state[SDL_SCANCODE_RIGHT] == state[SDL_SCANCODE_LEFT]) {
        game->man.dx *= 0.8f;
    }
    /*
	if(state[SDL_SCANCODE_DOWN])
	{
		game->man.y += 5;
	}
	*/
    if (state[SDL_SCANCODE_UP]) {
        game->man.dy = -15;
    }

    //scrolling

    if (game->man.x + game->man.w > game->rightScreen) {
        game->rightScreen = game->man.x + game->man.w;
        game->leftScreen = game->rightScreen - 920;

        game->scrollX = -(game->rightScreen - 1000);
    }
    if (game->man.x < game->leftScreen) {
        game->leftScreen = game->man.x;
        game->rightScreen = game->leftScreen + 920;

        game->scrollX = -(game->leftScreen - 80);
    }
    if (game->man.y < game->topScreen) {
        game->topScreen = game->man.y;
        game->bottomScreen = game->topScreen + 560;

        game->scrollY = -(game->topScreen - 80);
    }
    if (game->man.y + game->man.h > game->bottomScreen) {
        game->bottomScreen = game->man.y + game->man.h;
        game->topScreen = game->bottomScreen - 560;

        game->scrollY = -(game->bottomScreen - 560);
    }
    return done;
}

void collisionDetection(GameState* game)
{
    for (int i = 0; i < 100; ++i) {
        float mw = game->man.w, mh = game->man.h;
        float mx = game->man.x, my = game->man.y;
        float lx = game->ledges[i].x, ly = game->ledges[i].y, lw = game->ledges[i].w, lh = game->ledges[i].h;
        float vCheck = fabsf((my + mh / 2) - (ly + lh / 2));

        if (mx + mw > lx && mx < lx + lw && vCheck > 5) {
            if (game->man.dy > 0 && my + mh > ly && my < ly) {
                game->man.y = ly - mh;
                my = ly - mh;
                game->man.dy = 0;
            }

            if (game->man.dy < 0 && my < ly + lh && ly + lh < my + mh) {
                game->man.y = ly + lh;
                my = ly + lh;
                game->man.dy = 0;
            }
        }
        if (my + mh > ly && my < ly + lh) {
            if (game->man.dx > 0 && mx + mw > lx && mx < lx) {
                game->man.x = lx - mw;
                mx = lx - mw;
                game->man.dx = 0;
            }

            if (game->man.dx < 0 && mx < lx + lw && lx + lw < mx + mw) {
                game->man.x = lx + lw;
                mx = lx + lw;
                game->man.dx = 0;
            }
        }
    }
}

void processGravity(GameState* game)
{
    game->man.y += game->man.dy;
    game->man.dy += GRAVITY;
    game->man.x += game->man.dx;
}

SDL_Surface* load_image(char* imageName, GameState* game)
{
    SDL_Surface* surface = NULL;
    surface = IMG_Load(imageName);
    if (surface == NULL) {
        printf("could not load %s \b", imageName);
    }
    return surface;
}
void GameInit(GameState* game)
{
    // set the man to coo and correct size
    game->man.x = 100;
    game->man.y = 30;
    game->man.w = 60;
    game->man.h = 60;
    game->man.dy = 0;
    game->man.dx = 0;
    game->man.facingLeft = 0;

    // set where the screen start (now the man is in left corner)
    game->scrollX = 0;
    game->scrollY = 0;
    game->rightScreen = 1000;
    game->leftScreen = 80;
    game->bottomScreen = 640;
    game->topScreen = 80;

    // init all the ledges
    for (int i = 0; i < 100; ++i) {
        game->ledges[i].w = 50;
        game->ledges[i].h = 50;
        game->ledges[i].x = i * game->ledges[i].w;
        game->ledges[i].y = 670;
    }
    for (int i = 90; i < 100; i++) {
        game->ledges[i].x = 500 + (i - 90) * game->ledges[i].w;
        game->ledges[i].y = 450;
    }
    for (int i = 80; i < 90; i++) {
        game->ledges[i].x = 100 + (i - 80) * game->ledges[i].w;
        game->ledges[i].y = 620;
    }

    char backgroundSurface[50] = "background.png";
    char manSurface[50] = "man.png";
    char ledgesSurface[50] = "grass.png";

    game->bgTexture = SDL_CreateTextureFromSurface(
        game->renderer, load_image(backgroundSurface, game));
    SDL_FreeSurface(load_image(backgroundSurface, game));

    game->manTexture = SDL_CreateTextureFromSurface(game->renderer,
                                                    load_image(manSurface, game));
    SDL_FreeSurface(load_image(manSurface, game));

    game->ledgeTexture = SDL_CreateTextureFromSurface(
        game->renderer, load_image(ledgesSurface, game));
    SDL_FreeSurface(load_image(ledgesSurface, game));
}

void doRender(GameState* game)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
    SDL_RenderClear(game->renderer);

    SDL_Rect bgRect = {0, 0, 1080, 720};
    SDL_RenderCopy(game->renderer, game->bgTexture, NULL, &bgRect);

    for (int i = 0; i < 100; ++i) {
        SDL_Rect ledgeRect = {game->ledges[i].x + game->scrollX, game->ledges[i].y + game->scrollY, game->ledges[i].w, game->ledges[i].h};
        SDL_RenderCopy(game->renderer, game->ledgeTexture, NULL, &ledgeRect);
    }

    SDL_Rect manRect = {game->man.x + game->scrollX, game->man.y + game->scrollY, game->man.w, game->man.h};
    SDL_RenderCopyEx(game->renderer, game->manTexture, NULL, &manRect, 0, NULL, (game->man.facingLeft == 1));

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
        processGravity(&gameState);
        collisionDetection(&gameState);
        doRender(&gameState);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
    return 0;
}
