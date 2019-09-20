#ifndef PHYSICS_H
#define PHYSICS_H
#define GRAVITY 0.8f

void collisionDetection(GameState* game)
{
    for (int i = 0; i < 100; ++i) {
        float manWidth = game->man.w; 
	float manHeight = game->man.h;
        float manX = game->man.x;
	float manY = game->man.y;
        float ledgeX = game->ledges[i].x;
	float ledgeY = game->ledges[i].y;
	float ledgeWidth = game->ledges[i].w;
	float ledgeHeight = game->ledges[i].h;
        float vCheck = fabsf((manY + manHeight / 2) - (ledgeY + ledgeHeight / 2));

        if (manX + manWidth > ledgeX && manX < ledgeX + ledgeWidth && vCheck > 5) {
            if (game->man.dy > 0 && manY + manHeight > ledgeY && manY < ledgeY) {
                game->man.y = ledgeY - manHeight;
                manY = ledgeY - manHeight;
                game->man.dy = 0;
            }

            if (game->man.dy < 0 && manY < ledgeY + ledgeHeight && ledgeY + ledgeHeight < manY + manHeight) {
                game->man.y = ledgeY + ledgeHeight;
                manY = ledgeY + ledgeHeight;
                game->man.dy = 0;
            }
        }
        if (manY + manHeight > ledgeY && manY < ledgeY + ledgeHeight) {
            if (game->man.dx > 0 && manX + manWidth > ledgeX && manX < ledgeX) {
                game->man.x = ledgeX - manWidth;
                manX = ledgeX - manWidth;
                game->man.dx = 0;
            }

            if (game->man.dx < 0 && manX < ledgeX + ledgeWidth && ledgeX + ledgeWidth < manX + manWidth) {
                game->man.x = ledgeX + ledgeWidth;
                manX = ledgeX + ledgeWidth;
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
#endif
