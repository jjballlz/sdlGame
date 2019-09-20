#ifndef PHYSICS_H
#define PHYSICS_H
#define GRAVITY 0.8f

void collisionDetection(GameState* game)
{
    for (int i = 0; i < 100; ++i) {
        float mw = game->man.w, mh = game->man.h;
        float mx = game->man.x, my = game->man.y;
        float lx = game->ledges[i].x, ly = game->ledges[i].y, lw = game->ledges[i].w, lh = game->ledges[i].h;
        float vCheck = fabsf((my + mh / 2) - (ly + lh / 2));

        if (mx + mw > lx && mx < lx + lw && vCheck > 5) {
            if (game->man.dy > 0 && my + mh > ly && my < ly) {
                game->man.y = ly - mh;
                my = ly - mh;
                game->man.dy = 0;
            }

            if (game->man.dy < 0 && my < ly + lh && ly + lh < my + mh) {
                game->man.y = ly + lh;
                my = ly + lh;
                game->man.dy = 0;
            }
        }
        if (my + mh > ly && my < ly + lh) {
            if (game->man.dx > 0 && mx + mw > lx && mx < lx) {
                game->man.x = lx - mw;
                mx = lx - mw;
                game->man.dx = 0;
            }

            if (game->man.dx < 0 && mx < lx + lw && lx + lw < mx + mw) {
                game->man.x = lx + lw;
                mx = lx + lw;
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