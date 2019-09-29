#ifndef IMAGE_H
#define IMAGE_H

SDL_Surface* load(char* imageName)
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
    char starSurface[50] = "image/star.png";
    char staffSurface[50] = "image/staff.png";

    game->bgTexture = SDL_CreateTextureFromSurface(game->renderer, load(backgroundSurface));

    game->manTexture = SDL_CreateTextureFromSurface(game->renderer, load(manSurface));

    game->ledgeTexture = SDL_CreateTextureFromSurface(game->renderer, load(ledgesSurface));

    game->monstre1Texture = SDL_CreateTextureFromSurface(game->renderer, load(monstre1Surface));

    game->starTexture = SDL_CreateTextureFromSurface(game->renderer, load(starSurface));

    game->staffTexture = SDL_CreateTextureFromSurface(game->renderer, load(staffSurface));
}
#endif