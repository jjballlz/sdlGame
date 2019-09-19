#ifndef main_h
#define main_h

typedef struct
{
	float x, y, w, h;
	float dy;
	float dx;
	short life;
	char *name;
	int facingLeft;
} Man;

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

	Man man;

	Ledge ledges[100];

	SDL_Texture *bgTexture;
	SDL_Texture *manTexture;
	SDL_Texture *ledgeTexture;
	SDL_Renderer *renderer;
} GameState;

#endif
