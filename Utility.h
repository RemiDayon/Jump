#ifndef COMMON__H
#define COMMON__H

//--------------------WINDOW---------------------

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define SCREEN_CONTAIN(pos) (pos.x >= 0.f && pos.x < SCREEN_WIDTH && pos.y >= 0.f && pos.y < SCREEN_HEIGHT)

//--------------------TIME---------------------

#define DT (1/60.f)
#define MICROSECONDS(x) x * 1000000.f

//--------------------MATH---------------------

#define FRAND (rand() / (float) RAND_MAX)
#define DIST(u, v) sqrt((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y))
#define LENGTH(u) sqrt((u.x) * (u.x) + (u.) * (u.y))
#define LERP(a, b, f) ((1 - f) * a + b * f)
#define PI 3.14159265358
#define MIN(a, b) (a < b) ? a : b;
#define MAX(a, b) (a > b) ? a : b;
#define GAUS(x) exp(-500 * x * x)

//--------------------SFML---------------------

void sfCircleShape_centerOrigin(sfCircleShape* _fig);

void sfSprite_centerOrigin(sfSprite* _sprite);

void sfText_centerOrigin(sfText* _text);

sfSprite* sfSprite_loadFromFile(char* _name, int _isCentered);

void sfSprite_drawAt(sfSprite* _sprite, sfVector2f _position, sfRenderWindow* _window);

#endif // !COMMON__H