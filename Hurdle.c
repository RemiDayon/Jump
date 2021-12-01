#include "Hurdle.h"
#include "Utility.h"
#include <stdlib.h>
#include <SFML/Graphics/RenderWindow.h>

#define DIST_MIN 150.f
#define DIST_MAX 500.f

Hurdle* Hurdle_create(float _x)
{
	Hurdle* hurdle = malloc(sizeof(Hurdle));

	// loads the sprite of the hurdle
	hurdle->sprite = sfSprite_loadFromFile("resources/hurdle.png", sfTrue);
	//sfSprite_setOrigin(hurdle->sprite, (sfVector2f) { 32.f, 64.f });
	// sets the position of the hurdle
	hurdle->x = _x;
	hurdle->y[0] = 0.f;
	for (int x = 1; x < MAX_HURDLE; x++)
	{
		hurdle->y[x] = hurdle->y[x - 1] - (FRAND * (DIST_MAX - DIST_MIN) + DIST_MIN);
	}

	return hurdle;
}

void Hurdle_update(Hurdle* _hurdle, float _speed)
{
	for (int x = 0; x < MAX_HURDLE; x++)
	{
		_hurdle->y[x] += _speed * DT;

		// if a hurdle goes offscreen it is teleported at the top of the track
		// at a random position behin the last
		if (_hurdle->y[x] > SCREEN_HEIGHT + 64)
		{
			_hurdle->y[x] = _hurdle->y[(x + (MAX_HURDLE - 1)) % MAX_HURDLE] - (FRAND * (DIST_MAX - DIST_MIN) + DIST_MIN);
		}
	}
}

void Hurdle_draw(Hurdle* _hurdle, sfRenderWindow* _window)
{
	for (int x = 0; x < MAX_HURDLE; x++)
	{
		sfSprite_setPosition(_hurdle->sprite, (sfVector2f) { _hurdle->x, _hurdle->y[x] });
		sfRenderWindow_drawSprite(_window, _hurdle->sprite, NULL);
	}
}