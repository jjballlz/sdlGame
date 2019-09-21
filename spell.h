#ifndef SPELL_H
#define SPELL_H

void shoot_star(GameState* game)
{
    game->star[game->nbr_star].x = game->man.x;
    game->star[game->nbr_star].y = game->man.y;
    if (game->man.facingLeft == 1) {
        game->star[game->nbr_star].dx = -4;
        game->star[game->nbr_star].x += -15;
    } else {
        game->star[game->nbr_star].dx = +4;
        game->star[game->nbr_star].x += 35;
    }
    if (game->nbr_star < sizeof(game->star) / sizeof(game->star[0]) - 1) {
        game->nbr_star++;
    } else {
        game->nbr_star = 0;
    }
}

#endif