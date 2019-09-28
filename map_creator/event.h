#ifndef EVENT_H
#define EVENT_H
#include "spell.h"

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
    //test
    if (event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED) {
        game->nbr_ledges += 1;
    }
    if (event.button.button == SDL_BUTTON_RIGHT && event.button.state == SDL_PRESSED) {
        for (int i = 0; i < sizeof(game->ledges) / sizeof(game->ledges[0]); i++) {
            if (game->ledges[i].x != -666) {
                printf("ledge:\t%d\tx:\t%d\ty:\t%d\n", i, game->ledges[i].x, game->ledges[i].y);
            }
        }
    }
    if (state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT]) {
        game->man.dx -= 1;
        game->man.facingLeft = 1;
        if (game->man.dx <= -7) {
            game->man.dx = -7;
        }
    } else if (state[SDL_SCANCODE_RIGHT] && !state[SDL_SCANCODE_LEFT]) {
        game->man.dx += 1;
        game->man.facingLeft = 0;
        if (game->man.dx >= 7) {
            game->man.dx = 7;
        }
    } else {
        game->man.dx = 0;
    }

    if (state[SDL_SCANCODE_C]) {
        if (game->key_C == 0) {
            shoot_star(game);
            game->key_C = 1;
        }

    } else {
        game->key_C = 0;
    }
    if (state[SDL_SCANCODE_X]) {
        game->man.x = 500;
        game->man.y = 0;
        game->man.dy = 0;
    }

    //if (state[SDL_SCANCODE_RIGHT] == state[SDL_SCANCODE_LEFT]) {
    //    game->man.dx *= 0.8f;
    //}
    /*
	if(state[SDL_SCANCODE_DOWN])
	{
		game->man.y += 5;
	}
	*/
    if (state[SDL_SCANCODE_UP]) {
        game->man.dy = -8;
    }

    return done;
}
int scrolling_x(GameState* game)
{
    for (int i = 0; i < sizeof(game->ledges) / sizeof(game->ledges[0]); ++i) {
        game->ledges[i].x -= game->man.dx;
    }
    for (int i = 0; i < sizeof(game->star) / sizeof(game->star[0]); i++) {
        game->star[i].x -= game->man.dx;
    }
    game->scrollX += game->man.dx;
    if (game->scrollX >= 50) {
        game->scrollX -= 50;
    } else if (game->scrollX <= -50) {
        game->scrollX += 50;
    }
    game->monstre1.x -= game->man.dx;
}
int scrolling_y(GameState* game)
{
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
}
int scrolling(GameState* game)
{ //scrolling

    scrolling_x(game);
    scrolling_y(game);
}
#endif
