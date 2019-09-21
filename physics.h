#ifndef PHYSICS_H
#define PHYSICS_H
#define GRAVITY 0.8f

void collisionDetection(Humanoid* human, Ledge* ledge)
{
    // for (int i = 0; i < 100; ++i) {
    float manWidth = human->x;
    float manHeight = human->h;
    float manX = human->x;
    float manY = human->y;
    float ledgeX = ledge->x;
    float ledgeY = ledge->y;
    float ledgeWidth = ledge->w;
    float ledgeHeight = ledge->h;
    float vCheck = fabsf((manY + manHeight / 2) - (ledgeY + ledgeHeight / 2));

    if (manX + manWidth > ledgeX && manX < ledgeX + ledgeWidth && vCheck > 5) {
        if (human->dy > 0 && manY + manHeight > ledgeY && manY < ledgeY) {
            human->y = ledgeY - manHeight;
            manY = ledgeY - manHeight;
            human->dy = 0;
        }

        if (human->dy < 0 && manY < ledgeY + ledgeHeight && ledgeY + ledgeHeight < manY + manHeight) {
            human->y = ledgeY + ledgeHeight;
            manY = ledgeY + ledgeHeight;
            human->dy = 0;
        }
    }
    if (manY + manHeight > ledgeY && manY < ledgeY + ledgeHeight) {
        if (human->dx > 0 && manX + manWidth > ledgeX && manX < ledgeX) {
            human->x = ledgeX - manWidth;
            manX = ledgeX - manWidth;
            human->dx = 0;
        }

        if (human->dx < 0 && manX < ledgeX + ledgeWidth && ledgeX + ledgeWidth < manX + manWidth) {
            human->x = ledgeX + ledgeWidth;
            manX = ledgeX + ledgeWidth;
            human->dx = 0;
        }
    }
}
void processGravity(Humanoid* humanoide)
{
    humanoide->y += humanoide->dy;
    humanoide->dy += GRAVITY;
    humanoide->x += humanoide->dx;
}
#endif
