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
    int x, y, w, h;
} Ledge;

typedef struct
{
    float x, y;
    float dy;
} Star;

typedef struct
{
    float scrollX, scrollY;
    float rightScreen;
    float leftScreen;
    float topScreen, bottomScreen;

    Humanoid man;
    Humanoid monstre1;

    Ledge ledges[100];

    SDL_Texture* bgTexture;
    SDL_Texture* manTexture;
    SDL_Texture* monstre1Texture;
    SDL_Texture* ledgeTexture;
    SDL_Renderer* renderer;
} GameState;

#endif
