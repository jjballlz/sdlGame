#ifndef main_h
#define main_h

typedef struct
{
    float x, y, w, h;
    float dy;
    float dx;
    short life;
    char* name;
    int facingLeft;
} Humanoid;

typedef struct
{
    float x, y, w, h;
    float dy;
    float dx;
} Star;

typedef struct
{
    int x, y, w, h;
} Ledge;

typedef struct
{
    float scrollX, scrollY;
    float rightScreen;
    float leftScreen;
    float topScreen, bottomScreen;

    Humanoid man;
    Humanoid monstre1;

    Ledge ledges[100];
    Star star[10];
    int nbr_star;
    int key_C;

    SDL_Texture* bgTexture;
    SDL_Texture* manTexture;
    SDL_Texture* monstre1Texture;
    SDL_Texture* ledgeTexture;
    SDL_Texture* starTexture;
    SDL_Renderer* renderer;
} GameState;

#endif
