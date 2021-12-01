#include <stdlib.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Time.h>
#include <time.h>
#include "Game.h"
#include "Utility.h"

//------------------------GAME CREATE-----------------------

Game* GameCreate()
{
	Game* game = malloc(sizeof(Game));

	sfVideoMode mode = { SCREEN_WIDTH, SCREEN_HEIGHT };
	game->window = sfRenderWindow_create(mode, "pendule", sfDefaultStyle, NULL);
	game->world = World_create();
	sfRenderWindow_setKeyRepeatEnabled(game->window, sfFalse);
	return game;
}

//------------------------RUN-----------------------

// launchs the game object
void Run(Game* _game)
{
	// create the clock
	sfClock* clock = sfClock_create();
	sfTime elapsed = sfTime_Zero;

	while (sfRenderWindow_isOpen(_game->window))
	{
		elapsed.microseconds += sfClock_restart(clock).microseconds;
		// to avoid bug because of lag we
		// update with a constant frame rate
		while (sfTime_asSeconds(elapsed) >= DT)
		{
			elapsed.microseconds -= MICROSECONDS(DT);
			HandleEvent(_game);
			Update(_game);
		}

		Render(_game);
	}
}

//------------------------UPDATE-----------------------

// updates the game
void Update(Game* _game)
{
	World_update(_game->world);
}

//------------------------HANDLEEVENT-----------------------

// handles the event of the game
void HandleEvent(Game* _game)
{
	sfEvent event;
	while (sfRenderWindow_pollEvent(_game->window, &event))
	{
		if (event.type == sfEvtClosed)
		{
			sfRenderWindow_close(_game->window);
		}

		World_handleEvent(_game->world, event);
	}
}

//------------------------RENDER-----------------------

// draws all elements of the game
void Render(Game* _game)
{
	sfRenderWindow_clear(_game->window, sfBlack);
	World_draw(_game->world, _game->window);
	sfRenderWindow_display(_game->window);
}