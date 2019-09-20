#ifndef EVENT_H
#define EVENT_H

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
#endif
