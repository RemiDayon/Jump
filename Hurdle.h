#ifndef HURDLE_H
#define HURDLE_H

#include <SFML/Graphics/Sprite.h>

#define MAX_HURDLE 10

typedef struct
{
	sfSprite* sprite;
	float x;
	float y[MAX_HURDLE];
} Hurdle;

Hurdle* Hurdle_create(float _x);

void Hurdle_update(Hurdle* _hurdle, float _speed);

void Hurdle_draw(Hurdle* _hurdle, sfRenderWindow* _window);

#endif //HURDLE_H