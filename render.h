
#ifndef RENDER_H
#define RENDER_H
void render_ledges(GameState* game)
{
    for (int i = 0; i < sizeof(game->ledges) / sizeof(game->ledges[0]); ++i) {
        SDL_Rect ledgeRect = {game->ledges[i].x, game->ledges[i].y, game->ledges[i].w, game->ledges[i].h};
        SDL_RenderCopy(game->renderer, game->ledgeTexture, NULL, &ledgeRect);
    }
}

void render_stars(GameState* game)
{
    for (int i = 0; i < sizeof(game->star) / sizeof(game->star[0]); i++) {
        game->star[i].x += game->star[i].dx;
        SDL_Rect starRect = {game->star[i].x, game->star[i].y, game->star[i].w, game->star[i].h};
        SDL_RenderCopyEx(game->renderer, game->starTexture, NULL, &starRect, 0, NULL, 0);
    }
}

void render_monsters(GameState* game)
{
    SDL_Rect monstre1Rect = {game->monstre1.x, game->monstre1.y, game->monstre1.w, game->monstre1.h};
    SDL_RenderCopyEx(game->renderer, game->monstre1Texture, NULL, &monstre1Rect, 0, NULL, (game->monstre1.facingLeft == 1));
    show_life(&game->monstre1, game->renderer);
}

void render_man(GameState* game)
{
    show_life(&game->man, game->renderer);
    SDL_Rect manRect = {game->man.x, game->man.y, game->man.w, game->man.h};
    SDL_RenderCopyEx(game->renderer, game->manTexture, NULL, &manRect, 0, NULL, (game->man.facingLeft == 1));
}

void doRender(GameState* game)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
    SDL_RenderClear(game->renderer);

    SDL_Rect bgRect = {0, 0, 1080, 720};
    SDL_RenderCopy(game->renderer, game->bgTexture, NULL, &bgRect);

    render_ledges(game);
    render_stars(game);
    render_monsters(game);
    render_man(game);

    SDL_RenderPresent(game->renderer);
}
#endif