#ifndef IMAGE_H
#define IMAGE_H

SDL_Surface* load_image(char* imageName, GameState* game)
{
    SDL_Surface* surface = NULL;
    surface = IMG_Load(imageName);
    if (surface == NULL) {
        printf("could not load %s \n", imageName);
    }
    return surface;
}
void init_image(GameState* game)
{
    char backgroundSurface[50] = "image/background.png";
    char manSurface[50] = "image/man.png";
    char ledgesSurface[50] = "image/grass.png";
    char monstre1Surface[50] = "image/monstre1.png";

    game->bgTexture = SDL_CreateTextureFromSurface(
        game->renderer, load_image(backgroundSurface, game));
    SDL_FreeSurface(load_image(backgroundSurface, game));

    game->manTexture = SDL_CreateTextureFromSurface(game->renderer,
                                                    load_image(manSurface, game));
    SDL_FreeSurface(load_image(manSurface, game));

    game->ledgeTexture = SDL_CreateTextureFromSurface(
        game->renderer, load_image(ledgesSurface, game));
    SDL_FreeSurface(load_image(ledgesSurface, game));

    game->monstre1Texture = SDL_CreateTextureFromSurface(
        game->renderer, load_image(monstre1Surface, game));
    SDL_FreeSurface(load_image(monstre1Surface, game));
}
#endif