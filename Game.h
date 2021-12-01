#ifndef GAME__H
#define GAME__H

#include <SFML/Graphics/RenderWindow.h>
#include "World.h"

typedef struct
{
	sfRenderWindow* window;
	World* world;
} Game;

// creates a game with default parameter
Game* GameCreate();

// launchs the game object
void Run(Game* _game);

// updates the game
void Update(Game* _game);

// handles the event of the game
void HandleEvent(Game* _game);

// draws all elements of the game
void Render(Game* _game);

#endif // !GAME__H