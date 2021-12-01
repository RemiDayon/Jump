#ifndef WORLD__H
#define WORLD__H

#include <SFML/Graphics/RenderWindow.h>
#include "Player.h"

#define PLAYER_COUNT 4      
#define MAX_HURDLE 10
#define BACKGROUND 2

typedef enum
{
	SPT_BACKGROUND,
	SPT_TRACK,
	SPT_HURDLE,
	SPT_COUNT,
} SpriteNames;

typedef struct
{
	Player* player[PLAYER_COUNT];
	sfText* place[PLAYER_COUNT];
	char* texts[PLAYER_COUNT];
} World;

World* World_create();

void World_handleEvent(World* _world, sfEvent _event);

void World_update(World* _world);

void World_draw(World* _world, sfRenderWindow* _window);

#endif //!WORD__H
