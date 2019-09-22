#ifndef PHYSICS_H
#define PHYSICS_H
#define GRAVITY 1
void collisionDetection(GameState* game)
{
    printf("\n\nstar for");
    for (int i = 0; i < 100; ++i) {
        int manWidth = game->man.w;
        int manHeight = game->man.h;
        int manX = game->man.x;
        int manY = game->man.y;
        int ledgeX = game->ledges[i].x;
        int ledgeY = game->ledges[i].y;
        int ledgeWidth = game->ledges[i].w;
        int ledgeHeight = game->ledges[i].h;
        int vCheck = fabsf((manY + manHeight / 2) - (ledgeY + ledgeHeight / 2));
        //check for collision in y
        if (((manX + manWidth > ledgeX) && (manX + manWidth < ledgeX + ledgeWidth)) || ((manX > ledgeX) && (manX < ledgeX + ledgeWidth))) {
            if ((manY + manHeight) > ledgeY && (manY + manHeight) < (ledgeY + ledgeHeight) || ((manY + manHeight) == ledgeY)) {
                if ((manY + manHeight) != ledgeY) {
                    int delta;
                    delta = fabsf((manY + manHeight) - ledgeY);
                    game->man.y -= delta;
                }
                game->man.dy = 0;
            }
            if (manY > ledgeY && manY < ledgeY + ledgeHeight) {
                if (manY != ledgeY + ledgeHeight) {
                    int delta;
                    delta = fabsf(ledgeY + ledgeHeight - manY);
                    game->man.y += delta;
                }
                game->man.dy = 0;
            }
        }
        if (((manY + manHeight > ledgeY) && (manY + manHeight < ledgeY + ledgeHeight)) || ((manY > ledgeY) && (manY < ledgeY + ledgeHeight)) || (manY + manHeight == ledgeY + ledgeHeight)) {
            printf("%d lateral\n", i);

            if (((manX + manWidth) > ledgeX && (manX + manWidth) < (ledgeX + ledgeWidth) || ((manX + manWidth) == ledgeX)) && (game->man.facingLeft == 0)) {
                printf("collision\n");
                game->man.dx = 0;
            }
            if ((manX > ledgeX && manX < ledgeX + ledgeWidth || (manX == (ledgeX + ledgeWidth))) && (game->man.facingLeft == 1)) {
                printf("collisionnnnn\n");
                game->man.dx = 0;
            }
        }
    }
}
void collisionDetectionMonster(GameState* game)
{
    for (int i = 0; i < 100; ++i) {
        float manWidth = game->monstre1.w;
        float manHeight = game->monstre1.h;
        float manX = game->monstre1.x;
        float manY = game->monstre1.y;
        float ledgeX = game->ledges[i].x;
        float ledgeY = game->ledges[i].y;
        float ledgeWidth = game->ledges[i].w;
        float ledgeHeight = game->ledges[i].h;
        float vCheck = fabsf((manY + manHeight / 2) - (ledgeY + ledgeHeight / 2));

        if (manX + manWidth > ledgeX && manX < ledgeX + ledgeWidth && vCheck > 5) {
            if (game->monstre1.dy > 0 && manY + manHeight > ledgeY && manY < ledgeY) {
                game->monstre1.y = ledgeY - manHeight;
                manY = ledgeY - manHeight;
                game->monstre1.dy = 0;
            }

            if (game->monstre1.dy < 0 && manY < ledgeY + ledgeHeight && ledgeY + ledgeHeight < manY + manHeight) {
                game->monstre1.y = ledgeY + ledgeHeight;
                manY = ledgeY + ledgeHeight;
                game->monstre1.dy = 0;
            }
        }
        if (manY + manHeight > ledgeY && manY < ledgeY + ledgeHeight) {
            if (game->monstre1.dx > 0 && manX + manWidth > ledgeX && manX < ledgeX) {
                game->monstre1.x = ledgeX - manWidth;
                manX = ledgeX - manWidth;
                game->monstre1.dx = 0;
            }

            if (game->monstre1.dx < 0 && manX < ledgeX + ledgeWidth && ledgeX + ledgeWidth < manX + manWidth) {
                game->monstre1.x = ledgeX + ledgeWidth;
                manX = ledgeX + ledgeWidth;
                game->monstre1.dx = 0;
            }
        }
    }
}
void processGravity(Humanoid* humanoide)
{
    humanoide->y += humanoide->dy;
    humanoide->dy += GRAVITY;
}
#endif
